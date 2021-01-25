#include "sensors.hpp"

Sensor::Sensor(int id, int pin, int address){
    this->id = id;
    this->pin = pin;
    this->address = address;
    this->state = IDLE;
}

void Sensor::init(){

}
void Sensor::readSensor(){
    
}

void Sensor::setClient(WiFiClient client){
    this->client = client;
}

void Sensor::setState(typeState_t state){
    this->state = state;
    this->sendToActuator();
}

void Sensor::sendToActuator(){
    char stringToSend[50];
    sprintf(stringToSend,"%d%d\r",this->id,this->state);
    if(this->client.connected()>0)
        this->client.write(stringToSend);
}

SensorShort::SensorShort(int id, int pin, int address) : Sensor(id, pin, address){
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);  
    delay(10); 
    digitalWrite(this->pin, HIGH);
    delay(10);
    digitalWrite(this->pin, LOW);
    delay(10);
}

void SensorShort::init(){
    digitalWrite(this->pin, HIGH);
    if(!this->lox.begin(this->address)) {
        Serial.println("Failed to boot a VL53L0X");
        while(1);
    }
    delay(10);
}

void SensorShort::readSensor(){
    VL53L0X_RangingMeasurementData_t measure;
    this->lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    if(measure.RangeStatus != 4) {
        if(measure.RangeMilliMeter >= 20 && measure.RangeMilliMeter <= 430 && this->state != HIGHENERGY){
            this->setState(HIGHENERGY);
        }else if(measure.RangeMilliMeter > 430 && measure.RangeMilliMeter <= 840 && this->state != MEDIUMENERGY ){
            this->setState(MEDIUMENERGY);
        }else if(measure.RangeMilliMeter > 840 && measure.RangeMilliMeter < 1270 && this->state != LOWENERGY){
            this->setState(LOWENERGY);
        }else if(measure.RangeMilliMeter > 1270 && this->state != IDLE){
            this->setState(IDLE);
        }
    }else if(this->state != IDLE){
        this->setState(IDLE);
    }
}

SensorLong::SensorLong(int id, int pin, int address) : Sensor(id, pin, address){
  this->distanceSensor = SFEVL53L1X(Wire, this->pin);
}

void SensorLong::init(){
  Wire.begin();

  this->distanceSensor.sensorOff();
  this->distanceSensor.sensorOn();
  this->distanceSensor.setI2CAddress(this->address);

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while(1);
  }

  distanceSensor.setDistanceModeLong();
}

void SensorLong::readSensor(){
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();

  if(distance <= 3700) {
    if(distance >= 20 && distance <= 430 && this->state != HIGHENERGY){
        this->setState(HIGHENERGY);
    }else if(distance > 430 && distance <= 840 && this->state != MEDIUMENERGY ){
        this->setState(MEDIUMENERGY);
    }else if(distance > 840 && distance < 1270 && this->state != LOWENERGY){
        this->setState(LOWENERGY);
    }else if(distance > 1270 && this->state != IDLE){
        this->setState(IDLE);
    }
  }else if(this->state != IDLE){
      this->setState(IDLE);
  }
}


void SensorBottom::readSensor(){

}
