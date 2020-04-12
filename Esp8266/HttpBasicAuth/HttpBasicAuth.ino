///// fuente1: https://randomnerdtutorials.com/esp8266-web-server/
///// fuente2: https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const char* www_username = "admin";
const char* www_password = "esp8266";

String header;
  
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  } else {
    Serial.println("WiFi Connect Sussesful");
    delay(1000);
  }
  ArduinoOTA.begin();

  server.on("/", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/plain", "Login OK");
  });
  server.begin();

  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  WiFiClient client = server.available();

  if (client) {
    char c = server.client.read();
    header += c;

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    // turns the GPIOs on and off
    if (header.indexOf("GET /5/on") >= 0) {
      Serial.println("GPIO 5 on");
      output5State = "on";
      digitalWrite(output5, HIGH);
    } else if (header.indexOf("GET /5/off") >= 0) {
      Serial.println("GPIO 5 off");
      output5State = "off";
      digitalWrite(output5, LOW);

      // ------ codigo htma -------

      client.println("<!DOCTYPE html><html>");
      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
      client.println("<link rel=\"icon\" href=\"data:,\">");
      // CSS to style the on/off buttons
      // Feel free to change the background-color and font-size attributes to fit your preferences
      client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
      client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
      client.println(".button2 {background-color: #77878A;}</style></head>");

      // Web Page Heading
      client.println("<body><h1>ESP8266 Web Server</h1>");

      // Display current state, and ON/OFF buttons for GPIO 5
      client.println("<p>GPIO 5 - State " + output5State + "</p>");
      // If the output5State is off, it displays the ON button
      if (output5State == "off") {
        client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
      } else {
        client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
      }

      // Display current state, and ON/OFF buttons for GPIO 4
      client.println("<p>GPIO 4 - State " + output4State + "</p>");
      // If the output4State is off, it displays the ON button
      if (output4State == "off") {
        client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
      } else {
        client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
      }
      client.println("</body></html>");

    } else {
      header = "";
      // Close the connection
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
    }
  }
