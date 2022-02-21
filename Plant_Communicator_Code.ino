//Cele Daly and Mary Clark
//CSC 332

int moisturePin = A0; 

// This is a set threshold that coresponds to the YL-69 sensor. This sensor's range is 0-1023 with the highest point indicating the driest environment.
// This threshold can be adapted based on the type of plant/ how much water a plant requires.  
int threshold = 250;


#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11 

//initalizing DHT11 Sensor 
DHT dht(DHTPIN, DHTTYPE);


void setup(){

//setup will initialize the leds & the two sensors (moisture and temp/humidity) 
pinMode(3, OUTPUT); //green
pinMode(4, OUTPUT); //red

// SOIL MOISTURE
    pinMode(moisturePin, INPUT);
    Serial.begin(9600);

// TEMP & HUMIDITY
    Serial.begin(9600);
    Serial.println(F("DHTxx test!"));

    dht.begin();

//this portion turns on the green led to indicate to the user that the system has started set up
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  
}


void loop(){

// SOIL MOISTURE
/*YL-69 sensor uses an electric current the runs between the two prongs of the sensor, this sensor has a reporting range of 0 - 1023. 
When the environment is perfectly conductive to electricity (i.e. high levels of water) the sensor will read a low numbers down to a sensor reading 0.
If the soil is not conductive to electricity (i.e. dry/low levels of water), the sensor will read higher numbers up to a max of 1023. 
*/
    int sensorValue = analogRead(moisturePin); 
    Serial.print("sensor value is: ");
    Serial.println(sensorValue);
 
    delay(1000);
   


// TEMP & HUMIDITY
/* This sensor collects tempurature and humidity data. 

*/
    delay(1000);
    float h = dht.readHumidity();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

    float hif = dht.computeHeatIndex(f, h);
  

// TESTING

  if(h <= 30.00 || h >= 60.00){
    Serial.println("NEEDS HELPPPPP! - humidity issue"); 
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
      
    //blinking the light so that the user understands that something is wrong
    //additionally helpful for users that understand the code, to indicate that the arduino is interating through the code
    delay(1000);                     
    digitalWrite(4, LOW);  
    }
  else if(f <= 60.00 || f >= 77.00){
    Serial.println("NEEDS HELPPPP! - temp issue");
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);                     
    digitalWrite(4, LOW);  
  }

  else if(sensorValue > threshold){
    Serial.println("NEEDS HELPPPP! - soil moisture issue");
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);                     
    digitalWrite(4, LOW);  
  }
  else{
    Serial.println("no help needed!");
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
 

  
}
