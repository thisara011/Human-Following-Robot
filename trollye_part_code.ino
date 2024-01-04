//Arduino Human Following Robot
// You have to install the AFMotor and NewPing library Before Uploading the sketch
// You can find all the required libraris from arduino library manager.



//include the library code:
#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

#define LEFT A5             // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define RIGHT A1              // Left IR sensor connected to analog pin A3 of Arduino Uno:
#define TRIGGER_PIN A2        // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A3           // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0; //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value:
 int d=10;
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//create motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

 Servo myservo; //create servo object to control the servo:
 int pos=0;     //variable to store the servo position:

void setup() { // the setup function runs only once when power on the board or reset the board:
  
   Serial.begin(9600); //initailize serial communication at 9600 bits per second:
   myservo.attach(10); // servo attached to pin 10 of Arduino UNO
{
for(pos = 90; pos <= 180; pos += 1){    // goes from 90 degrees to 180 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  } 
for(pos = 180; pos >= 0; pos-= 1) {     // goes from 180 degrees to 0 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
for(pos = 0; pos<=90; pos += 1) {       //goes from 180 degrees to 0 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
}
   pinMode(RIGHT, INPUT); //set analog pin RIGHT as an input:
   pinMode(LEFT, INPUT);  //set analog pin RIGHT as an input:
   stop();
}

// the lope function runs forever
void loop() {                             
  
delay(50);                                        //wait 50ms between pings:
distance = sonar.ping_cm();                       //send ping, get distance in cm and store it in 'distance' variable:
Serial.print("distance");                   
Serial.println(distance);                         // print the distance in serial monitor:


    Right_Value = !digitalRead(RIGHT);             // read the value from Right IR sensor:
    Left_Value = !digitalRead(LEFT);               // read the value from Left IR sensor:
 
Serial.print("RIGHT");                      
Serial.println(Right_Value);                      // print the right IR sensor value in serial monitor:
Serial.print("LEFT");                       
Serial.println(Left_Value);                       //print the left IR sensor value in serial monitor:

if((distance > 1) && (distance < d)){            //check wheather the ultrasonic sensor's value stays between 1 to 15.
                                                  //If the condition is 'true' then the statement below will execute:
  //Move Forward:
  Motor1.setSpeed(130);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(130);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(130);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(130);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  
}else if((Right_Value==1) && (Left_Value==0)) {   //If the condition is 'true' then the statement below will execute:
  
  //Turn right                                                
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 cloclwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(BACKWARD);  //rotate motor3 anticlockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(BACKWARD);  //rotate motor4 anticlockwise:
  delay(150);
  
}else if((Right_Value==0)&&(Left_Value==1)) {     //If the condition is 'true' then the statement below will execute:
  
  //Turn left
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(BACKWARD);  //rotate motor1 anticlockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(BACKWARD);  //rotate motor2 anticlockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  delay(150);
  
}else if(distance > d) {                          //If the condition is 'true' then the statement below will execute:
  
stop();
}

}

void stop(){
    //Stop
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
}