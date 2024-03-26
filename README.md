# Entry-alarm-system
A door entry alarm system built using 2 arduinos.

This project was built in a combined effort involving myself and my groupmate:

We designed an Arduino system which manages the entry of people in someone’s room: this involves giving potential visitors the option to ring a doorbell to see if they can be granted access to the person’s room. An LCD display will also be outside the door, this will be the main means of communication between the visitor and the person inside their room. The person in the room can then respond to the visitor’s request to be granted entry by pressing a button inside their room to alert the pesky visitor if they are allowed entry as the LCD will display if they can enter the room. If for some reason, the insolent visitor does decide to intrude into the person’s room without their permission, there will be an alarm that will blare upon entry by the speaker. Their intrusion is detected by a motion sensor which monitors ¬¬¬ if the door has been opened. We found that this is the most optimal solution to our issue as it provides a non-confrontational way of repelling unwanted visitors, which provides the much-needed privacy every student is entitled to.

Literature and Technology review:

Having researched our potential solutions, we had a look at already existing entry control systems: most entry control systems make use of an intercom to notify the owner of the house if they are allowed to enter the house (Ring, 2022).
Pros:
- It makes it very easy for the owner to communicate with the visitor using an app.
- You don’t have to be in the house to let guests in.
- It’s more secure as you know who you are letting into your house.
Cons/reasons why we may not implement a similar system:
- It’s very difficult to implement a wireless communication system with Arduinos.
-The parts may become costly.
- We would need to develop a mobile app to control this which adds further complexity.
Taking inspiration from this, we decided to look at other systems provided by Ring, and they also provided doorbell systems which included a video doorbell system. This allows you to view who is trying to enter, and also speak to them before letting them in. (Ring, 2022)
Pros:
- You can see who is at the door so you know exactly who you are letting into your house.
-You can speak to the visitor.
-You have remote access to the controls via the app.
Cons/ reasons why we may not implement a similar system:
-The system is very difficult to develop as a project.
- It involves wireless communications which is rather complicated and may be too much for a small scale project.
- Voice communication will be very difficult to execute as it requires various different components that may be too much for an Arduino to handle.
Other sources of inspiration:
We took inspiration from an online post of an implementation of a speaker in a circuit: this involved creating a header file which contained the location of all the notes to be used by the speaker (Akshay James–YouTube, 2015). We used this as guidance on how to manage the speaker.
We also had a look at trip-wire alarm systems: these used wires to trigger the alarm, and they would be triggered when they were stepped on/broken (MrGear -Youtube, 2016). Using wires meant that moving around the room may be difficult, so we decided to use an ultrasonic sensor as it did not require any wires to trigger the alarm.
We had a look at online guide on the example code for I2C communications which described how the 2 Arduinos are wired and how they communicated with each other. (Zambetti, 2022)
Components used and why they were used: 
•	Ultrasonic sensor
o	Measures the distance from the sensor to the door
o	Can detect whether intruder opened the door without ringing doorbell
o	Our sensor measures distance that ranges from 1cm to 250cm
o	Advantages: not affected by object colour and transparency as it detects distance through sound waves, works well in dim places, consumes lower current/power
•	LCD display
o	To output messages to the visitor
o	Indicates whether visitor is allowed to enter the room
o	Can use the potentiometer to adjust brightness of LCD display
•	Pushbutton
o	Doorbell button: alerts the owner that someone is requesting entry access from outside the room
o	Second button: gives owner the choice to either grant or deny entry access for the visitor
o	Very simple, easy to interact
o	However, need to implement debouncing to make sure button press is only registering once 
•	Speaker
o	To alert the owner if the intruder entered the room without ringing the doorbell
o	Chose a speaker rather than a piezo buzzer because it has wider frequency range, so it’s much more versatile.
Overview of Development:
Our initial prototype of the solution was very similar to our final prototype:
Ultrasonic sensor:
In our initial prototype, we utilized an ultrasonic sensor to detect if the door was opened from a specific distance. During development we took inspiration from example Arduino code from the Arduino IDE (Arduino, 2022). The system would initially detect if the distance of the door from the sensor decreased, and if it did the alarm would trigger. The initial idea did not work as intended, as what would happen was that the pulse would be deflected away from the receiver which meant that the reading would display the maximum range of the ultrasonic sensor. Furthermore, the initial implementation also required wires to be very long and it would limit movement around the room, so we had to change the position of the ultrasonic sensor to be much closer to the door, i.e. perpendicular to the door. This was inspired by trip-wire alarm system which were often perpendicular to an entry point, but as we were using motion sensors, the wires would not limit our mobility (MrGear -Youtube, 2016). This meant that the detector would now detect the distance to the wall so when the door is opened, the pulse is interrupted. It also solves the issue of having to use very long cables which got in the way often.
Development of push buttons:
Having a look at most doorbell entry systems, we decided to use the most conventional and simplest way of alerting the person in the room, which is via a doorbell press. Initially, we implemented the button press with an attach-interrupt command, and it did work; however, multiple inputs were triggered sometimes during testing due to the physical limitations of buttons, so we took inspiration from example code via the Arduino sketchbook and IDE (Arduino, 2022) and used the debouncing code which only registers a button press a single time. We also included another button press which is responsible for sending the signal that the person in the room is allowing the visitor to enter their room.

Arduino communication:
Initially, we thought of using either Bluetooth or Wi-fi communication for our implementation. The main drawbacks to these approaches were the complexity of the implementation, and also the time constraint as we would also need to wait for the order of the modules to arrive which would cut into the development time. Consequently, we decided to have 2 Arduinos which were connected via I2C, one managed the means of communication between the visitor outside, and one which was responsible for tracking if the visitor enters the room without permission. To test for this we took inspiration from the example code and the Serial monitor to see if the buttons we developed earlier were transferring the correct signals from the controller Arduino to the agent Arduino.
LED Lights development:
 The Arduino responsible for communicating with the visitor outside had 2 LED lights connected parallel to each other. The green light would light up if the person was granted access to the room, and red light was displayed if the person entered the room without permission. This simple implementation was only used to test if the Arduinos communicated properly, and over the course of the development process, we utilized an LCD display instead which makes communicating with the visitor much easier and clearer rather than having lights as messages can be displayed on the LCD.

LCD implementation:
We quickly moved to an LCD implementation having figured out that the Arduinos communicated with each other. The LCD also made use of a potentiometer, which adjusted the contrast in the LCD to make it easier for the visitor to see the message displayed on the LCD. The LCD is responsible for displaying the text to “Ring the doorbell before entering”. This message would be displayed until one of the following occurred: the doorbell button is pressed, or the person walks in without ringing the doorbell. If the person does press the doorbell, the speaker will output the doorbell sound, which signals the person outside that there is a visitor outside, and “Please wait for response” is displayed on the LCD screen. If the person inside the room presses a button to let them know that they can come in, the LCD will then display “You can come in” on the screen. If they do ring the doorbell but the person inside does not respond and the visitor goes in without permission, the LCD will display “INTRUDER ALERT!” on the LCD and the speaker will blare an alarm.
Speaker development:
We took inspiration from an online post of an implementation of a speaker in a circuit: this involved creating a header file which contained the location of all the notes to be used by the speaker (Akshay James–YouTube, 2015). This implementation did not work too well for us as we didn’t utilize most of the notes in the header file containing the notes which would mean that the Arduino would be wasting storage that may be required. To circumvent this, we decided to implement a local integer array in the function responsible for triggering the doorbell ring and then used the tone function to play these notes when the doorbell button was pressed outside. We also thought of making use of the speaker to emit a sound when the alarm was triggered. During the testing process, our implementation made use of delays and this caused the alarm to play only a single note and we were unsure if this was a physical limitation of I2C as we did notice that the communication speed was quite slow, or if it was due to the delays that were responsible for making sure that the LCD displayed the text long enough on screen. We did try to fix this by reducing the amount of delays used in the code, however, the LCD would then not display the text long enough, and only one note would just play. Therefore, we decided to just play one note when the alarm is triggered.
Final prototype:
Inputs	Outputs
Potentiometer – used to adjust the contrast on the LCD.	LCD display - responsible for displaying the messages: “Ring doorbell before entering”, “Please wait for response”, “INTRDUER ALERT!”
Doorbell button – used to signal the Speaker to output the doorbell ring sound.	Speaker - outputs the doorbell ring sound if doorbell button pressed and the alarm sound if the alarm is triggered.
Answer button- used to accept the visitor’s request and signals the LCD to update to “You can come in”. 	Serial monitor (only used during testing) - used for monitoring if components worked as intended.
Ultrasonic sensor - used to detect if a door is opened without permission, if it is, then a signal is sent to the agent Arduino.	

Communication Method: I2C between 2 Arduinos.
How each component interacts with one another:
First Stage (1st case):
The potentiometer is adjusted to display the text on the LCD correctly. The LCD would display the message: “Ring the doorbell before entry.” The visitor would then need to press the doorbell button.
(2nd case): The person enters the room without pressing the doorbell which prompts the speaker to output the alarm sound and the LCD updates to display: “INTRUDER ALERT!”
Second Stage:
The speaker outputs the doorbell sound, and this would cause the LCD to update the current message to: “Please wait for response”.
Third Stage (1st case):
The person inside then presses the button to accept the visitor’s request. This sends a signal of “1” to the agent.

(2nd case): If there is no response and the person enters the room, the pulse from the ultrasonic sensor will be interrupted for a brief moment as the door blocks that initial signal: this then causes the controller Arduino to send a signal of “2” to the agent Arduino.
Fourth Stage (1st case):
Upon receiving “1”, the LCD will update to display: “You can come in”, and disables the ultrasonic sensor, so the alarm will not trigger when the person enters the room. 
(2nd case): Upon receiving a signal of “2”, the agent Arduino will make the LCD update to display: “INTRUDER ALERT!” and will output the alarm sound from the speaker.




Images of the system:
Master Arduino
![image](https://github.com/ZukoMcTaco/Entry-alarm-system/assets/112821163/49c511bb-dc95-4d72-a250-ae1f436c175b)
Servant Arduino
![image](https://github.com/ZukoMcTaco/Entry-alarm-system/assets/112821163/c9441b67-5500-4e4f-bfd4-26778bd276ba)
![image](https://github.com/ZukoMcTaco/Entry-alarm-system/assets/112821163/0aa175fc-1b21-4932-8090-fbbde2506a59)
Ultrasound System
![image](https://github.com/ZukoMcTaco/Entry-alarm-system/assets/112821163/58217595-4389-4c90-b2f1-896c4d07ef4c)



Schematic:
![image](https://github.com/ZukoMcTaco/Entry-alarm-system/assets/112821163/980ec969-c6c3-4cf9-8ee6-46947c4a610d)



