#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid      = "TP-LINK_903E";
const char* password  = "DmgZg2312";

ESP8266WebServer server(80);

char temp[400];
void handleRoot() {
  snprintf(temp, 400,                         /* HTML Doc*/
  "<html>\
  <head>\
  <meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\
  <title></title></head>\
  <body>\
  <h2>LED Status</h2>\
  <a href=\"/0\"><button>turn on</button></a>\
  <a href=\"/1\"><button>turn off</button></a>\
  </body>\
  </html>");
  server.send(200, "text\html", temp);
}

void turnon() {
  digitalWrite(2, HIGH);
  server.send(200, "text\html",temp);
}

void turnoff() {
  digitalWrite(2, LOW);
  server.send(200, "text\html", temp);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(2, OUTPUT);
  
  server.on("/", handleRoot);
  server.on("/1", turnon);
  server.on("/0", turnoff);
  server.begin();
  Serial.println("HTTP Server started!");
}

void loop() {
  server.handleClient();
}
