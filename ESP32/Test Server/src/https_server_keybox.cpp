#include "https_server_keybox.h"

https_server_keybox::https_server_keybox(/* args */) {
  if (start_spiffs()) Serial.println("SPIFFS ERROR");
}

https_server_keybox::~https_server_keybox() {}

void https_server_keybox::run() {
  // We pass:
  // serverTask - the function that should be run as separate task
  // "https443" - a name for the task (mainly used for logging)
  // 4096       - stack size in byte. If you want up to four clients, you should
  //              not go below 6kB. If your stack is too small, you will
  //              encounter Panic and stack canary exceptions, usually during
  //              the call to SSL_accept.
  // Priority of 2 for faster response time
  xTaskCreatePinnedToCore(serverTask, "https443", 4096, NULL, 2, NULL,
                          ARDUINO_RUNNING_CORE);
}

/** @brief This is a more generic demo for the query parameters. It makes use of
 * the iterator interface to access them, which is useful if you do not know the
 * paramter names in adavance.
 */
void handleRessources(httpsserver::HTTPRequest* req,
                      httpsserver::HTTPResponse* res) {
  // A word of warning: In this example, we use the query parameters and
  // directly print them into the HTML output. We do this to simplify the demo.
  // NEVER do this in a real application, as it allows cross-site-scripting.
  res->setHeader("Content-Type", "text/html");

  res->println(
      "<!DOCTYPE html><html><head><title>Query Parameter "
      "Demo</title></head><body><p>The following query paramters have been "
      "set:</p>");

  // Start a table to display the parameters
  res->println(
      "<table style=\"border:1px solid black "
      "collapse;\"><tr><th>Key</th><th>Value</th></tr>");

  // Iterate over the parameters. For more information, read about the C++
  // standard template library, especially about vectors and iterators.
  httpsserver::ResourceParameters* params = req->getParams();
  for (auto it = params->beginQueryParameters();
       it != params->endQueryParameters(); ++it) {
    res->print("<tr><td>");

    // The iterator yields std::pairs of std::strings. The first value contains
    // the parameter key
    res->printStd((*it).first);
    res->print("</td><td>");

    // and the second value contains the parameter value
    res->printStd((*it).second);
    res->println("</td></tr>");
  }
  res->println("</table>");

  // You can retrieve the total parameter count from the parameters instance:
  res->print("<p>There are a total of ");
  res->print(params->getQueryParameterCount());
  res->print(" parameters, with ");
  res->print(params->getQueryParameterCount(true));
  res->println(" unique keys.</p>");

  res->println("<p>Go <a href=\"/\">back to main page</a>.</p></body></html>");
}

/**
 * @brief This handler function will try to load the requested resource from
 * SPIFFS's / folder. If the method is not GET or POST, it will throw 405, if
 * the file is not found, it will throw 404.
 */
void handleSPIFFS(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res) {
  // We only handle GET here
  if (req->getMethod() == "GET" || req->getMethod() == "POST") {
    // Redirect / to /index.html
    std::string reqFile =
        req->getRequestString() == "/" ? "/index.htm" : req->getRequestString();

    // Try to open the file
    std::string filename = std::string("") + reqFile;

    // Check if the file exists
    if (!SPIFFS.exists(filename.c_str())) {
      Serial.print("File not found :");
      Serial.println(filename.c_str());
      // Send "404 Not Found" as response, as the file doesn't seem to exist
      res->setStatusCode(404);
      res->setStatusText("Not found");
      res->println("404 Not Found");
      return;
    }

    File file = SPIFFS.open(filename.c_str());

    // Set length
    res->setHeader("Content-Length", httpsserver::intToString(file.size()));

    // Content-Type is guessed using the definition of the contentTypes-table
    // defined above
    int cTypeIdx = 0;
    do {
      if (reqFile.rfind(contentTypes[cTypeIdx][0]) != std::string::npos) {
        res->setHeader("Content-Type", contentTypes[cTypeIdx][1]);
        break;
      }
      cTypeIdx += 1;
    } while (strlen(contentTypes[cTypeIdx][0]) > 0);

    // Read the file and write it to the response
    uint8_t buffer[256];
    size_t length = 0;
    do {
      length = file.read(buffer, 256);
      res->write(buffer, length);
    } while (length > 0);

    file.close();
  } else {
    // If there's any body, discard it
    req->discardRequestBody();
    // Send "405 Method not allowed" as response
    res->setStatusCode(405);
    res->setStatusText("Method not allowed");
    res->println("405 Method not allowed");
  }
}

void https_server_keybox::serverTask(void* params) {
  // In the separate task we first do everything that we would have done in the
  // setup() function, if we would run the server synchronously.

  // Note: The second task has its own stack, so you need to think about where
  // you create the server's resources and how to make sure that the server
  // can access everything it needs to access. Also make sure that concurrent
  // access is no problem in your sketch or implement countermeasures like locks
  // or mutexes.

  // Create nodes
  httpsserver::ResourceNode* spiffsNode =
      new httpsserver::ResourceNode("", "", &handleSPIFFS);
  httpsserver::ResourceNode* nodeQueryDemo =
      new httpsserver::ResourceNode("/index", "GET", &handleRessources);

  // Add nodes to the server
  // We register the SPIFFS handler as the default node, so every request that
  // does not hit any other node will be redirected to the file system.
  secureServer.setDefaultNode(spiffsNode);
  secureServer.registerNode(nodeQueryDemo);

  Serial.println("Starting server...");
  secureServer.start();
  if (secureServer.isRunning()) {
    Serial.println("Server ready.");

    // "loop()" function of the separate task
    while (true) {
      // This call will let the server do its work
      secureServer.loop();

      // Other code would go here...
      delay(1);
    }
  }
}