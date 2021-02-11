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
/**
 * @brief SensorState give a state for the sensors, if something is near, or far away, and how much the actuator should vibrate
 * 
 */
typedef enum SensorState{
    IDLE = 255,
    LOWENERGY = 170,
    MEDIUMENERGY = 85,
    HIGHENERGY = 0
}typeState_t;

/**
 * @brief Sensor is a mother class for each type of sensors
 * 
 */
class Sensor{
private:
    WiFiClient client;
    int id;
    /**
     * @brief sendToActuator use socket to send information to actuators
     * 
     */
    void sendToActuator();

protected:
    int address;
    int pin;
    typeState_t state = IDLE;
    /**
     * @brief setState change the state of the sensor and give information to sendToActuator()
     * 
     * @param state the new state of the sensor
     */
    void setState(typeState_t state);

public:
    /**
     * @brief Sensor Construct a new Sensor common to each type of sensors
     * 
     * @param id id of the sensor
     * @param pin pin of the xshut of the sensor
     * @param address address of the sensor
     */
    Sensor(int id, int pin, int address);
    /**
     * @brief init virtual function to be call by the child classes for each type of sensor
     * 
     */
    virtual void init(){}
    /**
     * @brief setClient give the client object to the class to send information 
     * 
     * @param client object client
     */
    void setClient(WiFiClient client);
    /**
     * @brief readSensor virtual function to be call by child classes
     * 
     */
    virtual void readSensor(){}
};

class SensorShort : public Sensor{
protected:
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();

public:
    /**
     * @brief SensorShort constructor for the short sensors
     * 
     * @param id id of the sensor
     * @param pin pin of the sensor's xshut
     * @param address address of the sensor
     */
    SensorShort(int id, int pin, int address);
    /**
     * @brief init initialisation of the sensors
     * 
     */
    void init();
    /**
     * @brief readSensor function to get the distance of potential obstacles
     * 
     */
    virtual void readSensor();
};

/**
 * @brief SensorLong inherits from the Sensor class. It is a simple wrapper around the SFEVL53L1X class.
 * 
 * It allows you to declare and use a VL53L1X sensor ("long range" type - 4m) with a common API used accross all sensors.
 */
class SensorLong : public Sensor{
protected:
    SFEVL53L1X distanceSensor;
public:

    /** 
     * @brief Create an instance of SensorLong
     * 
     * @param id unique identifier used to represent the sensors to use with actuators
     * @param pin used to shutdown the sensor for I2C 
     * @param address unique I2C physical address
     * 
     * @return newly initialized sensor
     */
    SensorLong(int id, int pin, int address);

   /** 
   * @brief Initialize the sensor
   */
    void init();
    
    /**
     * @brief Read the sensor's data and sends the appropriate state to the actuators
     */
    void readSensor();
};