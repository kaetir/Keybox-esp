/**
 * Example for the ESP32 HTTP(S) Webserver
 *
 * IMPORTANT NOTE:
 * To run this script, your need to
 *  1) Enter your WiFi SSID and PSK below this comment
 *  2) Make sure to have certificate data available. You will find a
 *     shell script and instructions to do so in the library folder
 *     under extras/
 *
 * This script will install an HTTPS Server on your ESP32 with the following
 * functionalities:
 *  - Show simple page on web server root
 *  - 404 for everything else
 * The server will be run in a separate task, so that you can do your own stuff
 * in the loop() function.
 * Everything else is just like the Static-Page example
 */

#include "creditential.h"

/** Check if we have multiple cores */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Include certificate data (see note above)
#include "cert.h"
#include "private_key.h"

// We will use wifi
#include <WiFi.h>

// Includes for the server
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <HTTPSServer.hpp>
#include <SSLCert.hpp>

// We will use SPIFFS and FS
#include <FS.h>
#include <SPIFFS.h>
// We need to specify some content-type mapping, so the resources get delivered with the
// right content type and are displayed correctly in the browser
char contentTypes[][2][32] = {
    { ".htm", "text/html" },
    { ".html", "text/html" },
    { ".css", "text/css" },
    { ".js", "application/javascript" },
    { ".json", "application/json" },
    { ".png", "image/png" },
    { ".jpg", "image/jpg" },
    { "", "" }
};

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

// Create an SSL certificate object from the files included above
SSLCert cert = SSLCert(
    example_crt_DER, example_crt_DER_len,
    example_key_DER, example_key_DER_len);

// Create an SSL-enabled server that uses the certificate
HTTPSServer secureServer = HTTPSServer(&cert);

// Declare some handler functions for the various URLs on the server
void handleRoot(HTTPRequest* req, HTTPResponse* res);
void handleRessources(HTTPRequest* req, HTTPResponse* res);
void handleSPIFFS(HTTPRequest* req, HTTPResponse* res);

// We declare a function that will be the entry-point for the task that is going to be
// created.
void serverTask(void* params);

void setup()
{
    // For logging
    Serial.begin(115200);

    // Try to mount SPIFFS without formatting on failure
    if (!SPIFFS.begin(false)) {
        // If SPIFFS does not work, we wait for serial connection...
        while (!Serial)
            ;
        delay(1000);

        // Ask to format SPIFFS using serial interface
        Serial.print("Mounting SPIFFS failed. Try formatting? (y/n): ");
        while (!Serial.available())
            ;
        Serial.println();

        // If the user did not accept to try formatting SPIFFS or formatting failed:
        if (Serial.read() != 'y' || !SPIFFS.begin(true)) {
            Serial.println("SPIFFS not available. Stop.");
            while (true)
                ;
        }
        Serial.println("SPIFFS has been formated.");
    }
    Serial.println("SPIFFS has been mounted.");
    File root = SPIFFS.open("/");

    File file = root.openNextFile();

    while (file) {

        Serial.print("FILE: ");
        Serial.println(file.name());

        file = root.openNextFile();
    }
    // Connect to WiFi
    Serial.println("Setting up WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("Connected. IP=");
    Serial.println(WiFi.localIP());

    // Setup the server as a separate task.
    Serial.println("Creating server task... ");
    // We pass:
    // serverTask - the function that should be run as separate task
    // "https443" - a name for the task (mainly used for logging)
    // 6144       - stack size in byte. If you want up to four clients, you should
    //              not go below 6kB. If your stack is too small, you will encounter
    //              Panic and stack canary exceptions, usually during the call to
    //              SSL_accept.
    xTaskCreatePinnedToCore(serverTask, "https443", 6144, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

void loop() {}

void serverTask(void* params)
{
    // In the separate task we first do everything that we would have done in the
    // setup() function, if we would run the server synchronously.

    // Note: The second task has its own stack, so you need to think about where
    // you create the server's resources and how to make sure that the server
    // can access everything it needs to access. Also make sure that concurrent
    // access is no problem in your sketch or implement countermeasures like locks
    // or mutexes.

    // Create nodes
    ResourceNode* spiffsNode = new ResourceNode("", "", &handleSPIFFS);
    ResourceNode* nodeRoot = new ResourceNode("/", "GET", &handleRoot);
    ResourceNode* nodeQueryDemo = new ResourceNode("/index", "GET", &handleRessources);

    // Add nodes to the server
    // We register the SPIFFS handler as the default node, so every request that does
    // not hit any other node will be redirected to the file system.
    secureServer.setDefaultNode(spiffsNode);
    secureServer.registerNode(nodeRoot);
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

void handleRoot(HTTPRequest* req, HTTPResponse* res)
{
    // Status code is 200 OK by default.
    // We want to deliver a simple HTML page, so we send a corresponding content type:
    res->setHeader("Content-Type", "text/html");

    // The response implements the Print interface, so you can use it just like
    // you would write to Serial etc.
    res->println("<!DOCTYPE html>");
    res->println("<html>");
    res->println("<head><title>UpTime</title></head>");
    res->println("<body>");
    res->print("<p>Your server is running for ");
    // A bit of dynamic data: Show the uptime
    res->print((int)(millis() / 1000), DEC);
    res->println(" seconds.</p>");
    res->println("</body>");
    res->println("</html>");
}

// This is a more generic demo for the query parameters. It makes use of the iterator
// interface to access them, which is useful if you do not know the paramter names in
// adavance.
void handleRessources(HTTPRequest* req, HTTPResponse* res)
{
    // A word of warning: In this example, we use the query parameters and directly print
    // them into the HTML output. We do this to simplify the demo. NEVER do this in a
    // real application, as it allows cross-site-scripting.
    res->setHeader("Content-Type", "text/html");

    res->println("<!DOCTYPE html>");
    res->println("<html>");
    res->println("<head>");
    res->println("<title>Query Parameter Demo</title>");
    res->println("</head>");
    res->println("<body>");
    res->println("<p>The following query paramters have been set:</p>");

    // Start a table to display the parameters
    res->println("<table style=\"border:1px solid black collapse;\">");
    res->println("<tr><th>Key</th><th>Value</th></tr>");
    // Iterate over the parameters. For more information, read about the C++ standard template library,
    // especially about vectors and iterators.
    ResourceParameters* params = req->getParams();
    for (auto it = params->beginQueryParameters(); it != params->endQueryParameters(); ++it) {
        res->print("<tr><td>");

        // The iterator yields std::pairs of std::strings. The first value contains the parameter key
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

    res->println("<p>Go <a href=\"/\">back to main page</a>.</p>");
    res->println("</body>");
    res->println("</html>");
}

/**
 * This handler function will try to load the requested resource from SPIFFS's /public folder.
 * 
 * If the method is not GET, it will throw 405, if the file is not found, it will throw 404.
 */
void handleSPIFFS(HTTPRequest* req, HTTPResponse* res)
{

    // We only handle GET here
    if (req->getMethod() == "GET") {
        // Redirect / to /index.html
        std::string reqFile = req->getRequestString() == "/" ? "/index.htm" : req->getRequestString();

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

        // Content-Type is guessed using the definition of the contentTypes-table defined above
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