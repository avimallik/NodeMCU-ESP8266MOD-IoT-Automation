/**
 Author: Arunav Mallik Avi
 Description: Home appliance automation instruction source code for NodeMCU. 
 resposible to read HTTP Post request from "ARM Robolox" android application Web Service. 
 capable of turning on and off home appliances connected through NodeMCU IoT Platform 
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>    


// Set web server port number to 80
//WiFiServer server(80);

// Variable to store the HTTP request
String header;

//Our Wi-Fi ssdid and password
//const char* ssid = "Robolox"; //Put your Wi-Fi ssdid here
//const char* password = "12345678"; //Your Wi-Fi Password

String room_light = "0";
String mirror_light = "0";
String bed_light = "0";
String fan = "0";

//Fan Control
int motorPlus = D3;
int motorMinus = D4;

ESP8266WebServer server; //server variable

void setup() {
  initializePin(); //call function
  
  //Making Connection With netword
  //WiFi.begin(ssid, password);
  
  Serial.begin(115200);
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
   WiFiManager wifiManager;
   wifiManager.autoConnect("AutoConnectAP");
   
  //Serial.print("Searching Connection");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(".");
  Serial.print("IP Address: "); //Show the IP Address to access your NodeMCU
  Serial.print(WiFi.localIP());
  
  serverSection();
}

void loop() {
  server.handleClient();

}

void initializePin(){
  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
//  pinMode(D8, OUTPUT);

  pinMode(motorPlus,OUTPUT);
  pinMode(motorMinus,OUTPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
//  digitalWrite(D8, LOW);

  digitalWrite(motorPlus,LOW);
  digitalWrite(motorMinus,LOW);
  
}

void serverSection(){
  server.on("/", []() {
    server.send(200, "text/html", "<!DOCTYPE html><html><meta charset='UTF-8'><head></head><body><p style=\"background-color:green;text-align:center;color:white;padding:30px;\"><font size = 6pt>Arm Robolox IoT WebServer</p></font><center><a href='/room_light' style=\"background-color: #4CAF50;border: none;color: white;padding:45px;text-align: center;text-decoration: none;display: inline-block;font-size: 25px;margin: 4px 2px;cursor: pointer;width:300px;height:40px\">LED 1</a></center><center><a href='/mirror_light' style=\"background-color: #4CAF50;border: none;color: white;padding: 45px;text-align: center;text-decoration: none;display: inline-block;font-size: 25px;margin: 4px 2px;cursor: pointer;width:300px;height:40px\">LED 2</a></center><center><a href='/fan' style=\"background-color: #4CAF50;border: none;color: white;padding: 45px;text-align: center;text-decoration: none;display: inline-block;font-size: 25px;margin: 4px 2px;cursor: pointer;width:300px;height:40px\">MOTOR</a></center></body></html>");
  });

  server.on("/room_light", room_light_state);
  server.on("/mirror_light", mirror_light_state);
  server.on("/fan", fan_state);

  server.on("/status", all_state);
  server.begin();
}

void room_light_state(){
  if(room_light == "0"){
    room_light = "1";
    digitalWrite(D5, HIGH);
    server.send(200, "text/html", room_light);
  }else{
    room_light = "0";
    digitalWrite(D5, LOW);
    server.send(200, "text/html", room_light);
  }
}

void mirror_light_state(){
  if(mirror_light == "0"){
    mirror_light = "1";
    digitalWrite(D6, HIGH);
    server.send(200, "text/html", mirror_light);
  }else{
    mirror_light = "0";
    digitalWrite(D6, LOW);
    server.send(200, "text/html", mirror_light);
  }
}

void bed_light_state(){
  if(bed_light == "0"){
    bed_light = "1";
    digitalWrite(D7, HIGH);
    server.send(200, "text/html", bed_light);
  }else{
    bed_light = "0";
    digitalWrite(D7, LOW);
    server.send(200, "text/html", bed_light);
  }
}

void fan_state(){
  if(fan == "0"){
    fan = "1";
//    digitalWrite(D8, HIGH);

    digitalWrite(motorPlus,HIGH);
    digitalWrite(motorMinus,LOW);

    server.send(200, "text/html", fan);
  }else{
    fan = "0";
//    digitalWrite(D8, LOW);

    digitalWrite(motorPlus,LOW);
    digitalWrite(motorMinus,LOW);

    server.send(200, "text/html", fan);
  }
}

void all_state(){
  server.send(200, "text/html", "{'rl':'"+room_light+"','ml':'"+mirror_light+"','bl':'"+bed_light+"','fan':'"+fan+"'}");
}
