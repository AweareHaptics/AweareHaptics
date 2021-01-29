#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <Ticker.h>
#define NB_ACTUATORS 2
#define PIN 27
#define NB_CLIENTS 1

typedef struct Actuator{
  Ticker tick;
  char intensity;
  bool state;
  uint8_t period;
  uint8_t cycle;
}t_actuator;

const char *ssid = "Server Movuino";     
const char *password = "Adrienestsib0";
WiFiServer wifiServer(80, NB_CLIENTS);
t_actuator actuators[NB_ACTUATORS];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NB_ACTUATORS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(115200);    
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  pixels.begin();
  for(int i = 0; i< NB_ACTUATORS; i++){
    reset(i);
    pixels.setPixelColor(i, pixels.Color(actuators[i].intensity,0,0));
  }
  pixels.show();
}
void reset(uint8_t id){
  actuators[id].tick.detach();
  actuators[id].cycle = 0;
  actuators[id].period = 0;
  actuators[id].state = false;
  actuators[id].intensity = 255;
  pixels.setPixelColor(i, pixels.Color(actuators[id].intensity,0,0));
  pixels.show();
}

void blink(uint8_t id){
  if(actuators[id].cycle * actuators[id].period > 3){
    reset(id);
    pixels.setPixelColor(i, pixels.Color(actuators[id].intensity,0,0));
    return;
  }

  if(actuators[id].state){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  }else{
    pixels.setPixelColor(i, pixels.Color(actuators[id].intensity,0,0));
  }
  pixels.show();
  actuators[id].state = !actuators[id].state;
  actuators[id].cycle++;
}

void loop() {
  uint8_t i, intensity;
  WiFiClient client = wifiServer.available();
    if(client){
      while (client.connected()) {
        while (client.available()>0) {
          String line = client.read();
          i = line[0];
          intensity = line[1];
          reset(i);
          if(intensity == 170){
            actuators[i].period = 1;
            actuators[i].intensity = intensity;
          }else if(intensity == 85){
            actuators[i].period = 0.5;
            actuators[i].intensity = intensity;
          }else if(intensity == 0){
            actuators[i].period = 0.2;
            actuators[i].intensity = intensity;
          }
          if(intensity != 255)
            actuators[i].tick.attach(actuators[i].period, blink, i);
        }
      }
      client.stop();
    }
}
