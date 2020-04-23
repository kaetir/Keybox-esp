#include "https_server_keybox.h"

Wallet* wallet2;
// We need to specify some content-type mapping, so the resources get delivered
// with the right content type and are displayed correctly in the browser
char contentTypes[][2][32] = {
    {".htm", "text/html"},         {".html", "text/html"},
    {".css", "text/css"},          {".js", "application/javascript"},
    {".json", "application/json"}, {".png", "image/png"},
    {".jpg", "image/jpg"},         {"", ""}};

// Include certificate data (see note above)
#include "cert.h"
#include "private_key.h"

https_server_keybox::https_server_keybox(Wallet* w)
    : cert(example_crt_DER, example_crt_DER_len, example_key_DER,
           example_key_DER_len),
      secureServer(&cert) {
  wallet2 = w;
}

https_server_keybox::~https_server_keybox() {}

/** @brief This is a more generic demo for the query parameters. It makes use of
 * the iterator interface to access them, which is useful if you do not know the
 * paramter names in adavance.
 */
void handleParams(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res) {
  // Iterate over the parameters. For more information, read about the C++
  // standard template library, especially about vectors and iterators.
  httpsserver::ResourceParameters* params = req->getParams();
  for (auto it = params->beginQueryParameters();
       it != params->endQueryParameters(); ++it) {
    // The iterator yields std::pairs of std::strings. The first value contains
    // the parameter key
    res->printStd((*it).first);
    res->print(" : ");
    // and the second value contains the parameter value
    res->printStd((*it).second);
  }
  // You can retrieve the total parameter count from the parameters instance:
  res->print("<p>There are a total of ");
  res->print(params->getQueryParameterCount());
  res->print(" parameters, with ");
  res->print(params->getQueryParameterCount(true));
  res->println(" unique keys.</p>");
}

/**
 * @brief This handler function will try to load the requested resource from
 * SPIFFS's / folder. If the method is not GET or POST, it will throw 405, if
 * the file is not found, it will throw 404.
 */
void handleSPIFFS(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res) {
  // if (!wallet2->isWalletcreated()) {  // true if usable, false if poop
  //   res->println("PAS DE WALLET");
  //   return;
  // }

  // We only handle GET here
  if (req->getMethod() == "GET" || req->getMethod() == "POST") {
    // Redirect / to /index.html
    std::string reqFile =
        req->getRequestString() == "/" ? "/index.htm" : req->getRequestString();

    // Try to open the file
    std::string filename = std::string("/web") + reqFile;

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

/**
 * @brief fonction for the login page reception
 *
 */
void handleLogin(httpsserver::HTTPRequest* req,
                 httpsserver::HTTPResponse* res) {}

/**
 * @brief fonction for the create Wallet page
 *
 */
void handleCreate(httpsserver::HTTPRequest* req,
                  httpsserver::HTTPResponse* res) {
  std::string username, password;
  std::vector<std::pair<std::string, std::string>> params;
  byte buffer[1024];

  req->readBytes(buffer, 1024);
  params = https_server_keybox::decodeUrlEncode((char*)buffer);

  for (auto p : params) {
    if (p.first == "name") username = p.second;
    if (p.first == "main_password") password = p.second;
  }

  if (username.length() > 0 && password.length() > 0) {
    Serial.println("Creating the wallet");
    wallet2->createWallet(username, password);
  
    Serial.println("Unlock");
    wallet2->unlock(password);
  
    Serial.println("Add accounts");
    wallet2->addAccount("google", "thibault", "googlePassword");
    wallet2->addAccount("pornhub", "tantonin", "grosZizi69");

    Serial.println("Get accounts");
    std::vector<std::vector<std::string>> tmp_acc = wallet2->getAccounts();
    for(auto a : tmp_acc){
      for(auto b : a){
        Serial.println(b.c_str());
      }
      res->print(a[0].c_str());
    }

    
  }
}

void https_server_keybox::serverTask(void* params) {
  // In the separate task we first do everything that we would have done in
  // the setup() function, if we would run the server synchronously.

  // Note: The second task has its own stack, so you need to think about where
  // you create the server's resources and how to make sure that the server
  // can access everything it needs to access. Also make sure that concurrent
  // access is no problem in your sketch or implement countermeasures like
  // locks or mutexes.

  // Create nodes
  httpsserver::ResourceNode* spiffsNode =
      new httpsserver::ResourceNode("", "", &handleSPIFFS);
  httpsserver::ResourceNode* nodeQueryDemo =
      new httpsserver::ResourceNode("/index", "GET", &handleParams);
  httpsserver::ResourceNode* nodeLogin =
      new httpsserver::ResourceNode("/login", "POST", &handleLogin);
  httpsserver::ResourceNode* nodeCreate =
      new httpsserver::ResourceNode("/create", "POST", &handleCreate);

  // Add nodes to the server
  // We register the SPIFFS handler as the default node, so every request that
  // does not hit any other node will be redirected to the file system.
  ((https_server_keybox*)params)->secureServer.setDefaultNode(spiffsNode);
  ((https_server_keybox*)params)->secureServer.registerNode(nodeQueryDemo);
  ((https_server_keybox*)params)->secureServer.registerNode(nodeLogin);
  ((https_server_keybox*)params)->secureServer.registerNode(nodeCreate);

  // Serial.println("Starting server...");
  ((https_server_keybox*)params)->secureServer.start();
  if (((https_server_keybox*)params)->secureServer.isRunning()) {
    // Serial.println("Server ready.");

    // "loop()" function of the separate task
    while (true) {
      // This call will let the server do its work
      ((https_server_keybox*)params)->secureServer.loop();
      // Other code would go here...
      delay(10);
    }
  }
}

std::vector<std::pair<std::string, std::string>>
https_server_keybox::decodeUrlEncode(char* url) {
  std::vector<std::pair<std::string, std::string>> output;
  std::vector<std::string> keyValues;

  char* pch = strtok(url, "&");
  while (pch != NULL) {
    keyValues.push_back(pch);
    pch = strtok(NULL, "&");
  }

  for (auto kv : keyValues) {
    output.push_back(std::make_pair<std::string, std::string>(
        strtok((char*)kv.c_str(), "="), strtok(NULL, "=")));
  }

  return output;
}