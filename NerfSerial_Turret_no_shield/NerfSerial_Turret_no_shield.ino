// Removed stepper motor and turned small servo into X axis movement

#include <Servo.h>


//String userFire;
char userFire;

Servo myservo;  // create servo object to control a servo
Servo myservosmall;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
int posx = 90;    // variable to store the small servo position

int maxstep = 240; // granularity of steps. Map 180 degrees to this number. Let it be divisible by 4 because sweep is 4 steps
int mapos = maxstep/3;    // variable to store the servo position
int maposx = maxstep/3;    // variable to store the small servo position

//Standby on for TB6612FNG
//int STBY = 7; //standby

//Motor A

//int AIN1 = 9; //Direction
//int AIN2 = 10; //Direction

#define mos 3  // pwm
#define AIN1 9  // pwm
#define AIN2 10

//Motor B

//int BIN1 = 11; //Direction
//int BIN2 = 12; //Direction

#define BIN1 11 // pwm
#define BIN2 12


void setup() {
//  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.begin(74880);           // set up Serial library at 74880 bps 115200
  Serial.println("Panget Terminator!");

  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  myservosmall.attach(13);  // attaches the servo on pin 9 to the servo object




//Iint TB6612fng pins as ouput
//    pinMode(STBY, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

      // Turn off motors - Initial state
//   digitalWrite(STBY, LOW);
   digitalWrite(AIN1, LOW);
   digitalWrite(AIN2, LOW);
   digitalWrite(BIN1, LOW);
   digitalWrite(BIN2, LOW);
   digitalWrite(mos, LOW);

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
            pmove();
            delay(500);
            move(2,0);
            delay(2000);   
            stop(2);
            Serial.write("FIRING STOP....");   
            delay(1000);
            pstop();
          }// end of fire sequence

                  //  "s" means stop firing sequence.. This will move small servo and nerf motor
        else if (userFire == 's') {
           
            Serial.write("stopping all motors FIRING....");
            pstop();
            stop(2);
          }// end of stop sequence

        //  "u" and "d" means moving 1 degree up/down for UP/Down servo
        else if (userFire == 'u' and pos < maxstep) {
            pos = pos + 1;
            mapos = map(pos,0,maxstep,0,180);
            myservo.write(mapos); 
            delay(15);
//            Serial.write("Up by 3 degrees...."); 

          }// end of up sequence
          
         else if (userFire == 'd' and pos > 0)  {
            pos = pos - 1;
            mapos = map(pos,0,maxstep,0,180);
            myservo.write(mapos); 
            delay(15);
//            Serial.write("Down by 3 degrees....");

          }// end of down sequence
        
      
        //  "l" and "r" means moving 1 degree up/down for left/right of small servo
        else if (userFire == 'r' and posx < maxstep) {
            posx = posx + 1;
            maposx = map(posx,0,maxstep,0,180);
            myservosmall.write(maposx); 
            delay(15);
//            Serial.write("right by 3 degrees...."); 

          }// end of up sequence
          
         else if (userFire == 'l' and posx > 0)  {
            posx = posx - 1;
            maposx = map(posx,0,maxstep,0,180);
            myservosmall.write(maposx); 
            delay(15);
//            Serial.write("left by 3 degrees....");

          }// end of down sequence

 else if (userFire == 'x') {
           
            Serial.write("reverse load....");
              move(2,1);
            delay(3000);   
            stop(2);
             Serial.write("reverse stop....");

          }// end of unload sequence

        else if (userFire == 't') {
           
            Serial.write("motor test p start....");
            pmove();
            delay(3000);
            pstop();
            Serial.write("motor test p end....");

          }// end of test sequence

          else if (userFire == 'm' )  {   // Sweep X axis
            if (maposx < 180){
              maposx = maposx + 4;}
            else{
              maposx = maposx - 4;}
            myservosmall.write(maposx); 

             }// end of testmovement sequence

        }// end of Read from COM send by python

        
        
 }


 
void move(int motors, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

//  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motors == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
//    analogWrite(PWMA, speed);

  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
//    analogWrite(PWMB, speed);
  }
}


 
void pmove(){

//    write enable to mosfet connected to balista motor
//    digitalWrite(mos, HIGH);
    analogWrite(mos, 200);
}

void pstop(){

//    write enable to mosfet connected to balista motor
    digitalWrite(mos, LOW);
    
}

void stop(int motors){


  if(motors == 1){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
//    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
//    analogWrite(PWMB, speed); 
}

//  digitalWrite(STBY, LOW); //disable standby
} // End of stop sequence
 
