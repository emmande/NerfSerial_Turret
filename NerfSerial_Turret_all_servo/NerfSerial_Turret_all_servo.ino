// Removed stepper motor and turned small servo into X axis movement

#include <AFMotor.h>
#include <Servo.h>


//String userFire;
char userFire;

Servo myservo;  // create servo object to control a servo
Servo myservosmall;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int posx = 0;    // variable to store the small servo position

AF_DCMotor motor(4); // motor channel 4
AF_DCMotor motor_small(3);// motor channel 3

//AF_Stepper step_motor(32, 1); // Stepper motor on channel 1

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Panget Terminator test!");

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservosmall.attach(10);  // attaches the servo on pin 9 to the servo object

  // turn on motors
  motor.setSpeed(255);
  motor_small.setSpeed(255);

//  initialized as stopped
  motor.run(RELEASE);
  motor_small.run(RELEASE);

//  step_motor.setSpeed(300);  // 10 rpm   
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
            delay(2000);
            motor_small.run(FORWARD);
            delay(300);   
//            myservosmall.write(0); 
            motor_small.run(RELEASE);
            Serial.write("FIRING STOP....");   
            delay(300);
            motor.run(RELEASE);
          }// end of fire sequence

                  //  "f" means firing sequence.. This will move small servo and nerf motor
        else if (userFire == 's') {
           
            Serial.write("Rapid FIRING....");
            motor.run(FORWARD);
            delay(2000);
            motor_small.run(FORWARD);
            delay(3000);   
//            myservosmall.write(0); 
            motor_small.run(RELEASE);
            Serial.write("FIRING STOP....");   
            delay(300);    
            motor.run(RELEASE);
//            step_motor.release();
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
        
      
        //  "l" and "r" means moving 1 degree up/down for left/right of small servo
        else if (userFire == 'r' and posx < 180) {
            posx = posx + 1;
            myservosmall.write(posx); 
            Serial.write("right by 3 degrees...."); 

          }// end of up sequence
          
         else if (userFire == 'l' and posx > 0)  {
            posx = posx - 1;
            myservosmall.write(posx); 
            Serial.write("left by 3 degrees....");

          }// end of down sequence

          
//         else if (userFire == 'l' )  {
////            steppos = steppos - 1;
//            step_motor.step(10, BACKWARD, SINGLE); 
//            Serial.write("left by 7 degrees....");
//            step_motor.release(); 
//
//          }// end of down sequence
//
//          else if (userFire == 'r' )  {
////            steppos = steppos - 1;
//            step_motor.step(10, FORWARD, SINGLE); 
//            Serial.write("right by 7 degrees....");
//            step_motor.release(); 
//
//          }// end of down sequence
        }// end of Read from COM send by python

        
        
 }
 
