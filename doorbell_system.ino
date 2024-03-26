
// libraries imported

#include <LiquidCrystal.h>

#include <Wire.h>


// initialize the library by associating any needed LCD interface pin

//////////////////////////////////////////////

//LCD Pins
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Doorbell Pins and button states
int doorBellPin = 2;

int doorBellFlag;

int buttonState;

int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;

unsigned long debounceDelay = 50;

int reading;


int speakerPin=3;

////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);

  pinMode(doorBellPin, INPUT);

  // set up the LCD's number of columns and rows:

  // Print a message to the LCD.

  lcd.begin(16, 2);

}

 

void loop() {
/*
  main function loop that checks if an intrusion happens,
  also manages the doorbell press,
  and makes sure that the display returns to:
   "Ring doorbell before entering"
*/
 
  doorBellFlag = 0;

  reading = digitalRead(doorBellPin);

  intrusion_check();//receives a signal if an intruder enters the room
  lcd.clear();

  lcd.print("Ring doorbell");

  lcd.setCursor(0, 1);

  lcd.print("Before entering");


  delay(100);
  //debounce of the doorbell button
  if (reading != lastButtonState){
      //take the last debounce time as the current one
    lastDebounceTime=millis();

  }

  else if((millis()-lastDebounceTime)>debounceDelay){

    
    if (reading != buttonState){
      buttonState = reading;

      if (buttonState==HIGH){
        //trigger the door bell ringing
        doorBellFlag = 1;

        doorBellButton();
      }

    }
  }
  lastButtonState = reading;
}


void doorBellButton(){
  /*
  procedure that changes the lcd display to let the visitor
  know that they have pressed the doorbell
  */
  if (doorBellFlag == 1){
    Serial.write("button pressed");
    lcd.setCursor(0, 1);

    lcd.clear();

    lcd.clear();

    lcd.print("please wait for");

    lcd.setCursor(0, 1);

    lcd.print("response");
    
    ringing();//function that outputs the doorbell ringing sound

    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    delay(40000);
  }
}
  
void ringing(){
/*
  function that's responsible for
  playing the doorbell ringing sound
*/
  int pitches[] = {262, 330, 392, 523, 392, 330, 262};
  //integer array that contains the notes to be played by speaker
    for (int i = 0; i < 7; i++){
    tone(speakerPin, pitches[i], 200);
    delay(500);
    Serial.print("bell triggered \n");
  }
}


void receiveEvent(int howMany){
  /*
  procedure that manages the event upon receiving a signal from the master arduino
  */
  int signal_received=Wire.read();
  Serial.write("signal_received");
  Serial.println(signal_received);
  if (signal_received == 1){
    //the signal received to let the visitor know they can come in
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("You can come in");
    delay(1000);
  }
  else if (signal_received == 2){
    //the signal received when a person intrudes
    int alarm = 330;
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("INTRUDER ALERT!");
    tone(speakerPin, alarm, 200);
    delay(500);
    Serial.print("can't come in\n");
    delay(1000);
  }

}

void intrusion_check(){
  /*
  function that receives a signal
  to check if an intruder has entered the room
  */
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  delay(3000);
}