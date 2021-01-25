#include "sensors.hpp"
#define NB_SENSORS 3

// Set these to your desired credentials.
const char *Apssid = "Server Movuino";     //Give AccessPoint name whatever you like. (this will be Name of your esp32 HOTSPOT)
const char *Appassword = "Adrienestsib0";         //Password of your Esp32's hotspot,(minimum length 8 required)
WiFiServer wifiServer(80);

Sensor *sensors[NB_SENSORS];

void setup() {
  Serial.begin(115200);                   // To enable Serial Commmunication with connected esp32 board
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.mode(WIFI_AP);                    // Changing ESP32 wifi mode to AccessPoint

  // You can remove the Appassword parameter if you want the hotspot to be open.
  WiFi.softAP(Apssid, Appassword);      //Starting AccessPoint on given credential
  IPAddress myIP = WiFi.softAPIP();     //IP Address of our Esp8266 accesspoint(where we can host webpages, and see data)
  Serial.print("AP IP address: ");
  Serial.println(myIP);                //Default IP is 192.168.4.1
  wifiServer.begin();
  sensors[0] = new SensorShort(0,27,0x30);
  sensors[1] = new SensorShort(1,14,0x31);
  sensors[2] = new SensorLong(2,15, 0x32);
  for(int i = 0; i < NB_SENSORS; i++)
    sensors[i]->init();
}

void loop() {
  WiFiClient client = wifiServer.available();
 
  if (client) {
    for(int i = 0; i < NB_SENSORS; i++)
      sensors[i]->setClient(client);
    while (client.connected()) {
      for(int i = 0; i < NB_SENSORS; i++)
        sensors[i]->readSensor();
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
    delay(100);
}
