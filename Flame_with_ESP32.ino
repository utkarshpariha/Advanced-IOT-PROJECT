#include <WiFi.h>

const char *ssid =  "Galaxy";     // Replace with your WIFI SSID
const char *pass =  "87654321 "; // Replace with your WIFI PASSWORD

void send_event(const char *event);
const char *host = "maker.ifttt.com";
const char *privateKey = "gkb_HtIpE-FeOWMH20obLTvUR7_fPipDyj_hdTJ****";

const int sensor = 13; 
const int LED = 2;
     
void setup() {
  Serial.begin(115200);  
  pinMode(sensor,INPUT);
  pinMode(LED,OUTPUT);
         
   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
  int output = digitalRead(sensor);
   if (output==1) {           
  Serial.print("FIRE DETECTED!"); 
  digitalWrite(LED,HIGH); 
  send_event("FIRE DETECTION");  
  }
digitalWrite(LED,LOW);
}

void send_event(const char *event)
{
  Serial.print("Connecting to "); 
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}
