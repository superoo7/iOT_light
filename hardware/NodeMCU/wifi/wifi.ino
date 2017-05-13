#include "ESP8266WiFi.h"

// WiFI WPA2
const char* ssid = "";      // ssid
const char* password = "";  // password

int ledPin = 13; // GPIO13
WiFiServer server(80);

void wifiSetup();
void startServer();

void setup() {
  Serial.begin(115200);
  wifiSetup();
}

void loop() {
  startServer();
}


void wifiSetup() {
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void startServer() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

// Set ledPin according to the request
//digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><title>On/Off LED</title><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\"><script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script></head><body class=\"container\"><h1 class=\"text-center\">Led pin is now: ");

  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("</h1></div class=\"text-center col-lg-12 col-md-12 col-xs-12\"><br /><a class=\"text-center col-lg-12 col-md-12 col-xs-12\" href=\"/LED=ON\"><button type=\"button\" class=\"col-lg-12 col-md-12 col-xs-12 btn btn-lg btn-success\">Turn On</button></a><br><br><br /><br /><a class=\"text-center col-lg-12 col-md-12 col-xs-12\" href=\"/LED=OFF\"><button type=\"button\" class=\"col-lg-12 col-md-12 col-xs-12 btn btn-lg btn-danger\">Turn Off</button></a></body></html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

