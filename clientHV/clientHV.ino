#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <Ticker.h>
#define NB_ACTUATORS 1
#define PIN 27
#define NB_CLIENTS 1

const char *ssid = "Server Movuino";     
const char *password = "Adrienestsib0";
WiFiServer wifiServer(80, NB_CLIENTS);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NB_ACTUATORS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);    
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  pixels.begin();
  for(int i = 0; i< NB_ACTUATORS; i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  }
  pixels.show();
}


void loop() {
  uint8_t i, intensity;
  WiFiClient client = wifiServer.available();
    if(client){
      while (client.connected()) {
        while (client.available()>0) {
          uint8_t line[2];
          client.read(line, 2);
          i = line[0];
          intensity = line[1];
          Serial.print(i);
          Serial.println(intensity);
          if(i < NB_ACTUATORS){
            pixels.setPixelColor(i, pixels.Color(intensity,0,0));
            pixels.show();
          }
          delay(10);
        }
      }
      client.stop();
    }
}
