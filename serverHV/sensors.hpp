#include <WiFi.h> 
#include "Adafruit_VL53L0X.h"

// includes for long range sensors
#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <Wire.h>
#include <vl53l1_error_codes.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

typedef enum SensorState{
    IDLE = 255,
    LOWENERGY = 170,
    MEDIUMENERGY = 85,
    HIGHENERGY = 0
}typeState_t;

class Sensor{
private:
    WiFiClient client;
    int id;

    void sendToActuator();

protected:
    int address;
    int pin;
    typeState_t state = IDLE;

    void setState(typeState_t state);

public:
    Sensor(int id, int pin, int address);
    virtual void init(){}
    void setClient(WiFiClient client);
    virtual void readSensor(){}
};

class SensorShort : public Sensor{
protected:
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();

public:
    SensorShort(int id, int pin, int address);
    void init();
    virtual void readSensor();
};

class SensorLong : public Sensor{
protected:
    SFEVL53L1X distanceSensor;
public:
    SensorLong(int id, int pin, int address);
    void init();
    void readSensor();
};

class SensorBottom : public SensorShort{
public:
    SensorBottom(int id, int pin, int address) : SensorShort(id, pin, address){}
    void readSensor();
};