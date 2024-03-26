// Imported library
#include <Wire.h>
//Pins
const int pingPin = 8;

const int answer_button = 4;
//flags, button states, and constants

int sensor_flag = 1;

int buttonState;

int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;

unsigned long debounceDelay = 50;

int reading;


/*signal that will be sent when the two
arduinos communicate with each other
*/
byte signal;

void setup() {
/*
function that initiates the answer button
*/
  Wire.begin();
  Serial.begin(9600);
  pinMode(answer_button,INPUT);

}

void pingDetection(){
  /*
  procedure that manages the ultrasonic detection:
      if the sensor is meant to be on,
      a pulse is sent by the ultrasonic sensor
      and calculates the distance to the wall.
      if the signal is interrupted,
      a signal is sent to the other arduino to update it.
  */
  long duration;
  long distance;
  if (sensor_flag == 1){

    pinMode(pingPin,OUTPUT);

    digitalWrite(pingPin,LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin,LOW);

    pinMode(pingPin,INPUT);
    duration=pulseIn(pingPin,HIGH);

    distance= distanceConverter(duration);
    Serial.print(distance);
    Serial.print("cm \n");

    if (distance < 234){
      Serial.print("Door is not open \n");
    }
    else if (distance > 234){
      /*if door is open send signal:"2"
        to the other arduino*/
      Serial.print("door is open \n");
      signal=2;
      sendSignal();
    }
    }

}

void sendSignal(){
  /*
  procedure which sends the appropriate signal 
  to the agent arduino
  */
  digitalWrite(pingPin,LOW);

  delay(10000);

  Wire.beginTransmission(8);
  Wire.write(signal);
  Wire.endTransmission();
  sensor_flag = 1;

  delay(1000);

}

long distanceConverter(long time){
  /*
  function that returns the distance from the 
  ultrasonic sensor to the wall, or any object that interrupts the pulse
  */
  return (time/128);
}


void loop() {
  /*
  main loop function
  that manages the answer button, and
  the ultrasonic sensor.
  */
  int reading = digitalRead(answer_button);

  pingDetection();
//debounce
  if (reading != lastButtonState){
      //take last debounce time as the current one
      lastDebounceTime = millis();

    }
  else if((millis()-lastDebounceTime>debounceDelay)){

    if (reading != buttonState){
      buttonState = reading;

      if (buttonState == HIGH){
        //if answer button pressed, send signal to other arduino
        sensor_flag=0;
         signal=1;
         Serial.print("You are allowed to enter \n");
         sendSignal();    
      }
    }
  }
lastButtonState=reading;
  }


