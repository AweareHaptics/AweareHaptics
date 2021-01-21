#include <WiFi.h> 
#include "Adafruit_VL53L0X.h"
typedef enum SensorState{
    IDLE = 0,
    LOWENERGY = 1,
    MEDIUMENERGY = 2,
    HIGHENERGY = 3
}typeState_t;
class Sensor{
    private:
    int id;
    int address;
    int pin;
    typeState_t state;
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();

    void setState(typeState_t state, WiFiClient client);
    void sendToActuator(WiFiClient client);

    public:
    Sensor(int id, int pin, int address);
    void init();
    void readSensor(WiFiClient client);
};
