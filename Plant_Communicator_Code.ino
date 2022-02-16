int moisturePin = A0;
int threshold = 950;


#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);


void setup(){

pinMode(3, OUTPUT); //green
pinMode(4, OUTPUT); //red

// SOIL MOISTURE
    pinMode(moisturePin, INPUT);
    Serial.begin(9600);

// TEMP & HUMIDITY
    Serial.begin(9600);
    Serial.println(F("DHTxx test!"));

    dht.begin();

    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  
}

void loop(){


// SOIL MOISTURE
    int sensorValue = analogRead(moisturePin); 
    Serial.print("sensor value is: ");
    Serial.println(sensorValue);
 
    delay(1000);
   


// TEMP & HUMIDITY
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
