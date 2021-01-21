#include "sensors.hpp"

Sensor::Sensor(int id, int pin, int address){
    this->id = id;
    this->pin = pin;
    this->address = address;
    this->state = IDLE;
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);  
    delay(10); 
    digitalWrite(this->pin, HIGH);
    delay(10);
    digitalWrite(this->pin, LOW);
}

void Sensor::init(){
    digitalWrite(this->pin, HIGH);
    if(!this->lox.begin(this->address)) {
        Serial.println("Failed to boot a VL53L0X");
        while(1);
    }
    delay(10);
}
void Sensor::readSensor(WiFiClient client){
    VL53L0X_RangingMeasurementData_t measure;
    char stringToSend[50];
    this->lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    if(measure.RangeStatus != 4) {
        sprintf(stringToSend,"Sensor n°%d value : %d",this->id,measure.RangeMilliMeter);
        if(measure.RangeMilliMeter >= 20 && measure.RangeMilliMeter <= 430 && this->state != HIGHENERGY){
            this->setState(HIGHENERGY, client);
        }else if(measure.RangeMilliMeter > 430 && measure.RangeMilliMeter <= 840 && this->state != MEDIUMENERGY ){
            this->setState(MEDIUMENERGY, client);
        }else if(measure.RangeMilliMeter > 840 && measure.RangeMilliMeter < 1270 && this->state != LOWENERGY){
            this->setState(LOWENERGY, client);
        }else if(measure.RangeMilliMeter > 1270 && this->state != IDLE){
            this->setState(IDLE, client);
        }
        sprintf(stringToSend, "%s state : %d",stringToSend, this->state);
        Serial.println(stringToSend);
    }else if(this->state != IDLE){
        this->setState(IDLE, client);
    }
}
void Sensor::setState(typeState_t state, WiFiClient client){
    this->state = state;
    this->sendToActuator(client);
}

void Sensor::sendToActuator(WiFiClient client){
    char stringToSend[50];
    sprintf(stringToSend,"%d%d\r",this->id,this->state);
    if(client.connected()>0)
        client.write(stringToSend);
}
