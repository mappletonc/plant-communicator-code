The code begins with the initialization of the analog pin that feeds information from the moisture sensor to the Arduino board, and consequently to the serial monitor.  Then the next line of code will set the threshold that corresponds to the YL-69 sensor. This sensor's range is 0-1023 with the highest point indicating the driest environment. The threshold can be adapted based on the type of plant and how much water a plant requires.  

int moisturePin = A0; 
int threshold = 950;


The following portion of the code is to initialize the use of the DHT sensor—ie the device that measures humidity and temperature. The first line includes the library relevant to the sensor, the following line indicates which pin the sensor is connected to, and the final line defines the type of DHT Sensor that is being used. 


#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11 

This line will define parameters to initialize the DHT11 Sensor.  
DHT dht(DHTPIN, DHTTYPE);


void setup(){
Set up will initialize the leds & calibrate the two sensors: The YL-69 moisture sensor and the DHT11 temp and humidity sensor. This DHT11 sensor is on the top right in the attached image. The orange wire will connect the signal pin to the digital 2 pin.  The YL-69 moisture sensor is attached to the breadboard in the bottom right corner of the image using a potentiometer. The potentiometer’s signal pin is connected to the A0 analog pin with the yellow wire.
The leds are powered using the green wires connected to the digital 3 and 4 pins, which is controlled by the code below

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


void loop(){

The sensors will begin to operate on a continuous loop testing the temperature, humidity, and moisture of the given plant. 

// SOIL MOISTURE
YL-69 sensor uses an electric current that runs between the two prongs of the sensor, this sensor has a reporting range of 0 - 1023. 
When the environment is perfectly conductive to electricity (i.e. high levels of water) the sensor will read a low number down to a sensor reading 0.
If the soil is not conductive to electricity (i.e. dry/low levels of water), the sensor will read higher numbers up to a max of 1023. 

This portion of the code will set the variable ‘sensorValue’ to whatever number the YL-69 sensor reads for that instance through the loop. Then it will print the value for the user’s benefit in understanding what specific number is being produced. 
 
    int sensorValue = analogRead(moisturePin); 
    Serial.print("sensor value is: ");
    Serial.println(sensorValue);
 
This sensor will read on a delay. 
    delay(1000);
   


// TEMP & HUMIDITY
This DHT11 sensor collects temperature and humidity data. It will initialize two float variables to track the humidity percentage and the temperature in fahrenheit.   
    delay(1000);
    float h = dht.readHumidity();
    float f = dht.readTemperature(true);

This portion is meant to be a double check to ensure that the sensor is reading the information properly, and will fail out if it is not. 
    if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

    

// TESTING
The rest of the code will be checking the conditions recorded by the sensors to see if they are conducive to plant growth and life. It will begin with humidity, then temperature, and finally ending with the soil moisture. 
//humidity 
  if(h <= 30.00 || h >= 60.00){
      digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
      
We have written code for a blinking red led so that the user understands that something is wrong. Additionally it will be helpful for users that understand the code, to indicate that the Arduino is iterating through the loop

This will hold the light on with delay, then will turn it off. 
    delay(1000);                     
    digitalWrite(4, LOW);  
    }

//temperature
 
Temperature and the moisture sensors will operate on the same principles as the humidity loop, this includes the delay to blink the led. 
  else if(f <= 60.00 || f >= 77.00){
       digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);                     
    digitalWrite(4, LOW);  
  }

  else if(sensorValue > threshold){
     digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);                     
    digitalWrite(4, LOW);  
  }

The final aspect of the if/else loop is an else statement is an else statement that will keep or change the green led to be on to indicate that the plant is in the ideal conditions. 

  else{
    Serial.println("no help needed!");
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }  
}
