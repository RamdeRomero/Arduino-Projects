#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>

#include <FS.h>   //Include File System Headers

#include <Ultrasonic.h>

Ultrasonic ultrasonic(D1, D2); //D1 trig, D2=echo

int distance;


const char* htmlfile = "/index.html";

 

//WiFi Connection configuration

const char* ssid = "PLDTHOMEFIBRr8dGV";  //Your Wifi SSID

const char* password = "Romerofam#123";  //Your wifi password

 

  ESP8266WebServer server(80);

 

void handleADC(){

  distance = ultrasonic.read();

  String adc = String(distance);

  Serial.print("Cm : ");

  Serial.println(adc);

  server.send(200, "text/plane",adc); //sends data to server

}

 

void handleRoot(){

  server.sendHeader("Location", "/index.html",true);   //Redirect to our html web page

  server.send(302, "text/plane","");

}

 

void handleWebRequests(){

  if(loadFromSpiffs(server.uri())) return;

  String message = "File Not Detected\n\n";

  message += "URI: ";

  message += server.uri();

  message += "\nMethod: ";

  message += (server.method() == HTTP_GET)?"GET":"POST";

  message += "\nArguments: ";

  message += server.args();

  message += "\n";

  for (uint8_t i=0; i<server.args(); i++){

    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";

  }

  server.send(404, "text/plain", message);

  Serial.println(message);

}

 

void setup() {

  delay(1000);

  Serial.begin(115200);

  Serial.println();

 

 

             //Initialize File System

  SPIFFS.begin();

  Serial.println("File System Initialized");

  Serial.print("Setting AP (Access Point)…");

  Serial.println();

  

  WiFi.begin(ssid, password);             // Connect to the network

  Serial.print("Connecting to ");

  Serial.print(ssid); Serial.println(" ...");


 // Wait for connection

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }


  //If connection successful show IP address in serial monitor

  Serial.println("");

  Serial.print("Connected to ");

  Serial.println(ssid);

  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

 


              //Initialize Webserver

  server.on("/",handleRoot);

  server.on("/getADC",handleADC); //Reads ADC function is called from out index.html

  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI

  server.begin();

  Serial.println("HTTP server started"); 

}

 

void loop() {

 server.handleClient();

}

 

bool loadFromSpiffs(String path){

  String dataType = "text/plain";

  if(path.endsWith("/")) path += "index.htm";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));

  else if(path.endsWith(".html")) dataType = "text/html";

  else if(path.endsWith(".htm")) dataType = "text/html";

  else if(path.endsWith(".css")) dataType = "text/css";

  else if(path.endsWith(".js")) dataType = "application/javascript";

  else if(path.endsWith(".png")) dataType = "image/png";

  else if(path.endsWith(".gif")) dataType = "image/gif";

  else if(path.endsWith(".jpg")) dataType = "image/jpeg";

  else if(path.endsWith(".ico")) dataType = "image/x-icon";

  else if(path.endsWith(".xml")) dataType = "text/xml";

  else if(path.endsWith(".pdf")) dataType = "application/pdf";

  else if(path.endsWith(".zip")) dataType = "application/zip";

  File dataFile = SPIFFS.open(path.c_str(), "r");

  if (server.hasArg("download")) dataType = "application/octet-stream";

  if (server.streamFile(dataFile, dataType) != dataFile.size()) {

  }

 

  dataFile.close();

  return true;

}
