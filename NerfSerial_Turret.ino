// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include <AFMotor.h>
#include <Servo.h>

//String userFire;
char userFire;

Servo myservo;  // create servo object to control a servo
Servo myservosmall;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

AF_DCMotor motor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Panget Terminator test!");

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservosmall.attach(10);  // attaches the servo on pin 9 to the servo object

  // turn on motor
  motor.setSpeed(255);
 
  motor.run(RELEASE);
}

void loop() {
//  uint8_t i;
  
//  Read data from serial
      if (Serial.available()> 0){
//        userFire = Serial.readStringUntil('\n');
        userFire = Serial.read();
        //  "f" means firing sequence.. This will move small servo and nerf motor
        if (userFire == 'f') {
           
            Serial.write("FIRING....");
            motor.run(FORWARD);
            delay(1000);
            myservosmall.write(180); 
            delay(300);   
            myservosmall.write(0); 
            Serial.write("FIRING STOP....");   
            delay(100);
            motor.run(RELEASE);
          }// end of fire sequence

                  //  "f" means firing sequence.. This will move small servo and nerf motor
        else if (userFire == 's') {
           
            Serial.write("Rapid FIRING....");
            motor.run(FORWARD);
            delay(1000);
            myservosmall.write(180); 
            delay(300);   
            myservosmall.write(0); 
            delay(300);   
            myservosmall.write(180);
            delay(300);   
            myservosmall.write(0); 
            delay(300);   
            myservosmall.write(180);
            delay(300);   
            myservosmall.write(0);
            Serial.write("FIRING STOP....");   
            delay(50);
            motor.run(RELEASE);
          }// end of fire sequence

        //  "u" and "d" means moving 1 degree up/down for UP/Down servo
        else if (userFire == 'u' and pos < 180) {
            pos = pos + 1;
            myservo.write(pos); 
            Serial.write("Up by 3 degrees...."); 

          }// end of up sequence
          
         else if (userFire == 'd' and pos > 0)  {
            pos = pos - 1;
            myservo.write(pos); 
            Serial.write("Down by 3 degrees....");

          }// end of down sequence
        
        }// end of Read from COM send by python

        
 }
 
