#include "sensors.hpp"
#define NB_SENSORS 2

const char *Apssid = "Server Movuino"; //Name of the hotspot wifi
const char *Appassword = "P@ssw0rd"; //password
const char * host = "192.168.4.2"; //Ip address of the server
const uint16_t port = 80; //port of the server


Sensor *sensors[NB_SENSORS];
/**
 * @brief Initialisation of sensors
 * 
 * We create a hotspot wifi and instanciate all sensors
 * 
 */
void setup() {
  Serial.begin(115200); 
  Serial.println("Configuring access point...");
  WiFi.mode(WIFI_AP); //ESP32 can now be a hotspot wifi

  WiFi.softAP(Apssid, Appassword); //We create the hotspot wifi

  /* 
    We initialize all sensors 
  */
  sensors[0] = new SensorLong(0,27,0x30);
  sensors[1] = new SensorShort(1,14,0x31);
  //sensors[2] = new SensorLong(2,15, 0x32);
  for(int i = 0; i < NB_SENSORS; i++)
    sensors[i]->init();
}

/**
 * @brief loop
 * 
 * We try to connect to the server (the actuators)
 * When we found it, we give the information to sensors and begin getting data for each sensors
 * 
 */
void loop() {
  WiFiClient client;
  // We try to connect to the server
  if (!client.connect(host, port)) {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  //If we are connected to the server
  if (client) {
    //We give the client to each sensors to let them send information
    for(int i = 0; i < NB_SENSORS; i++)
      sensors[i]->setClient(client);
    //While we are connected to the server we get the data of the sensors 
    while (client.connected()) {
      for(int i = 0; i < NB_SENSORS; i++)
        sensors[i]->readSensor();
 
      delay(100);
    }
  
    client.stop();
    Serial.println("Client disconnected");
 
  }
    delay(100);
}
