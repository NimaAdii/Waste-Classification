#include <Stepper.h>
#include <Servo.h>

// Constants
// (1)-Ultra Sonic & other pins

const int trigPin = 2;
const int echoPin = 3;
const int buttonPin = 4;            // to take the input of the button
const int endLED = 6;               // to indicate that the sealing process is over by red LED
const int coilPin = 7;              // power to coil
const int servo1Pin = 12;           // servo motor
const int servo2Pin = 13;
int compressingCyclesCompleted=0;
int totalCompressingCycles=2;
bool sealingStarted=false;

// (2)-Other measurements
const int compressingDistance = 10;   // Max distance for compressing in cm
const int sealingDistance = 10;       // Max distance for sealing in cm
const int sealingtime = 3000;         // Sealing time in ms

// Define the number of steps per revolution
const int stepsPerRevolution=200;

// Create a Stepper object with the number of steps per revolution and the motor control pins
Stepper myStepper(stepsPerRevolution,8,9,10,11); 
// Create servo object
Servo servo1;
Servo servo2;

// for if loop
bool isLoopStopped = false;       // Variable to track if the loop is stopped

void setup() {
  // Set the speed of the stepper motor
  myStepper.setSpeed(60);

  // Start the serial communication for debugging purposes
  Serial.begin(9600);

  // Set up the pins for ultrasonic sensor, LED and coil
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(endLED, OUTPUT);
  pinMode(coilPin, OUTPUT);

  // Attach servo to the servoPin
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
}

void loop() {

  if (!isLoopStopped) {
    
    // Measure the distance with the ultrasonic sensor
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration / 58; // Calculate 'd'

    // Print distance to the serial monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");          
    

    //Check if distance is less than the compressingDistance
    if (distance<compressingDistance && compressingCyclesCompleted<totalCompressingCycles){
      
        myStepper.step(stepsPerRevolution*10); // Compressing plate comes down
        delay(1000);
        
        myStepper.step(-stepsPerRevolution*10); // Compressing plate goes up
        delay(1000);

        compressingCyclesCompleted+=1;
        sealingStarted=false;
    }
        

    servo1.write(0);                    //initial position
    servo2.write(45);

    // Check if distance is less than the sealingDistance
    if (distance < sealingDistance && compressingCyclesCompleted==totalCompressingCycles && !sealingStarted) {
      sealingStarted=true;
      //Serial.println("Sealing starts");
      servo1.write(100);                // Turn the servo motor by 90 degrees
      delay(500);
      servo2.write(0);

      digitalWrite(coilPin,HIGH);       // supply current to coil through relay module
      delay(sealingtime);               // Wait for the servo to reach the desired position (Sealing time)
      digitalWrite(coilPin,LOW);        // off the power supply to coil

      servo2.write(45);
      delay(500);
      servo1.write(0);                  // Reset the servo to the initial position (0 degrees)
      
      digitalWrite(endLED,HIGH);        // light the red LED to indicate the process is over

      //Serial.println("Sealing completed. Stopping the loop.");
    
      isLoopStopped = true;

    }   
  }
  
  // Check if the button is pressed to restart the loop
  if (digitalRead(buttonPin) == LOW) {

    digitalWrite(endLED,LOW);         // Wait for the servo to reach the desired position
    //Serial.println("Button pressed. Restarting the loop.");
    compressingCyclesCompleted=0;
    sealingStarted=false;
    isLoopStopped = false;

  }
  delay(100);                         // Delay between measurements

}
