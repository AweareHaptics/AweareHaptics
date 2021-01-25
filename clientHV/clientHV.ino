#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#define NB_ACTUATORS 2
#define PIN 27

const char *ssid = "Server Movuino";     
const char *password = "Adrienestsib0";
WiFiServer wifiServer(80);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NB_ACTUATORS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(115200);    
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  pixels.begin();
  for(int i = 0; i< NB_ACTUATORS; i++)
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  pixels.show();
}

void loop() {
  int actuator, state;
  WiFiClient client = wifiServer.available();
    if(client){
      while (client.connected()) {
        while (client.available()>0) {
          String line = client.readStringUntil('\r');
          actuator = line[0] - '0';
          state = line[1] - '0';
          if(state == 0)
            pixels.setPixelColor(actuator, pixels.Color(255,0,0));
          else if(state == 1)
            pixels.setPixelColor(actuator, pixels.Color(170,0,0));
          else if(state == 2)
            pixels.setPixelColor(actuator, pixels.Color(85,0,0));
          else if(state == 3)
            pixels.setPixelColor(actuator, pixels.Color(0,0,0));
          pixels.show();
        }
      }
      client.stop();
    }
}
