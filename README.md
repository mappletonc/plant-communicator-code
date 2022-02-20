# plant-communicator-code
The code begins with the initialization of the analog pin that feeds information from the moisture sensor to the Arduino board, 
and consequently to the serial monitor.  Then the next line of code will set the threshold that corresponds to the YL-69 sensor. 
This sensor's range is 0-1023 with the highest point indicating the driest environment. The threshold can be adapted based on the
type of plant and how much water a plant requires.  

int moisturePin = A0; 
int threshold = 950;


The following portion of the code is to initialize the use of the DHT sensor—ie the device that measures humidity and temperature. 
The first line includes the library relevant to the sensor, the following line indicates which pin the sensor is connected to, and
the final line defines the type of DHT Sensor that is being used. 
#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11 

This line will define parameters to initialize the DHT11 Sensor.  
DHT dht(DHTPIN, DHTTYPE);


void setup(){
Set up will initialize the leds & calibrate the two sensors: The YL-69 moisture sensor and the DHT11 temp and humidity sensor. 

pinMode(3, OUTPUT); //green led
pinMode(4, OUTPUT); //red led

The code below will begin the operations of the sensors.

// SOIL MOISTURE
    pinMode(moisturePin, INPUT);
    Serial.begin(9600);

// TEMP & HUMIDITY
    Serial.begin(9600);
    Serial.println(F("DHTxx test!"));

    dht.begin();

This portion of the code will turn on the green led to indicate to the user that the system has started set up.
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  
}

