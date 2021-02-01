#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#define NB_ACTUATORS 1
#define PIN 27
#define NB_CLIENTS 1
#define ACTUATOR_ID 0
#define INTENSITY 1

const char *ssid = "Server Movuino";     
const char *password = "P@ssw0rd";
WiFiServer wifiServer(80, NB_CLIENTS);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NB_ACTUATORS, PIN, NEO_GRB + NEO_KHZ800);
/**
 * @brief Setup of the microcontroller
 * 
 * We initiate the actuators to low before all, then we try to connect to the hotspot wifi, and set up the server
 * 
 */
void setup() {
  Serial.begin(115200);  
  pixels.begin();
  //We set the actuators to low
  for(int i = 0; i< NB_ACTUATORS; i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  }
  //We send the data to actuators
  pixels.show();  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println(WiFi.localIP()); //The IP address should be 192.168.4.2
  wifiServer.begin();
}

/**
 * @brief loop 
 * 
 * We get a client if there is any, if there is no client avaible, the loop is finished
 * When a client is connected, we enter in a loop while there is a client
 * When a client is available, we receive data from the client and do the actions
 * 
 */
void loop() {
  WiFiClient client = wifiServer.available();
  if(client){
    while (client.connected()) {
      while (client.available()>0) {
        //We get and print the data received
        uint8_t line[2];
        client.read(line, 2);
        Serial.print("actuator id : ");
        Serial.print(line[ACTUATOR_ID]);
        Serial.print(" intensity : ");
        Serial.println(line[INTENSITY]);
        //If there is an actuator related to the sensor
        if(line[ACTUATOR_ID] < NB_ACTUATORS){
          //We change the state of the actuator
          pixels.setPixelColor(line[ACTUATOR_ID], pixels.Color(line[INTENSITY],0,0));
          pixels.show();
        }
        delay(10);
      }
    }
    client.stop();
  }
}
