#include <Servo.h>
Servo servoL;  // create servo object for left servo
Servo servoR;  // create servo object for right servo

// Define pins for ultrasonic sensor
int trigPin = 3;
int echoPin = 4;
int in_1 = 8 ;
int in_2 = 9 ;
int enA = 5;
String data;

// Define variables for measuring distance 
long duration;
float distance;

void setup() {


servoL.attach(6); // attach first servo to pin 6
servoR.attach(7); // attach second servo to pin 7

  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Set trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in_1,OUTPUT);
  pinMode(in_2,OUTPUT);
 

// Turn off the motor - Initial state

digitalWrite(in_1,LOW);
digitalWrite(in_2,LOW);


  
  // get output to light the led
  pinMode(13, OUTPUT);
  // Allow time for sensor to settle
  delay(1000);
}

void loop() {
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
// 30cm = Width of the walls of the conveyor belt
  if (distance < 30) {
    digitalWrite(in_1 , HIGH);
    digitalWrite(in_2 , LOW);
    delay(1000); // The time it takes to take the garbage from initial position to the IMGC unit
    digitalWrite(in_1, LOW);
    digitalWrite(in_2 , LOW);

    String data = "STOP"; // The string you want to send
    Serial.println(data); // Send the string data through the serial port
    delay(1000); // Delay between sending each string (optional)
// Garbage is positioned below the camera module

if (Serial.available()>0) { // check if there's incoming data
    String data = Serial.readString(); // read the incoming data until the terminating character
    Serial.println(data); // print the received data     
}


// If the servo rotates counter clock wise, initial (0) angle should be pointing to righ hand side
// Then initial position is angled 45 degrees to right hand side (Paper)
// if data == Wastefood, the servo should be angled at 45 degrees from servo motor's initial position
// if data == plastic, the servo should be angled at 90 degrees from servo motor's initial position
if (data == "Paper") {
    digitalWrite(in_1 , HIGH);
    digitalWrite(in_2 , LOW); // Drives the conveyor belt forward
    int angle1 = 0; // set the angle required for left servo 
    // Flap is angled at 45 degrees to right hand side (From forward direction)
    int angle2 = 0; // set the angle required for right servo
    servoL.write(angle1); // move first servo to the desired angle
    servoR.write(angle2); // move second servo to the desired angle
    delay(3000);}

 
if (data == "Wastefood") {
    digitalWrite(in_1 , HIGH);
    digitalWrite(in_2 , LOW); // Drives the conveyor belt forward
    int angle1 = 45; // set the angle required for left servo 
    // Flap is pointed parallel to the forward direction
    int angle2 = 45; // set the angle required for right servo
    servoL.write(angle1); // move first servo to the desired angle
    servoR.write(angle2); // move second servo to the desired angle
    delay(3000); }

if (data == "Polythene") {
    digitalWrite(in_1 , HIGH);
    digitalWrite(in_2 , LOW); // Drives the conveyor belt forward
    int angle1 = 90; // set the angle required for left servo 
    // Flap is angled at 45 degrees to left hand side
    int angle2 = 90; // set the angle required for right servo
    servoL.write(angle1); // move first servo to the desired angle
    servoR.write(angle2); // move second servo to the desired angle
    delay(3000); }

else {
  digitalWrite(in_1 , LOW);
    digitalWrite(in_2 , HIGH);
    delay(1000); // The time it takes to take the garbage from initial position to the IMGC unit (Same time as mentioned above)
    digitalWrite(in_1, LOW);
    digitalWrite(in_2 , LOW);}
  }
    
  }else {
    digitalWrite(in_1, LOW);
    digitalWrite(in_2 , LOW);
  }


    
}
