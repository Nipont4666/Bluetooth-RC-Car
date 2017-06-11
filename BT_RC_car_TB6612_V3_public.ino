/*****************************************************************************/
 /* Written by Pason Tanpaiboon // 02-06-2017 V.1.2
 /* Project: Bluetooth RC car via Arduino Bluetooth with Android Application
 /* 03/6/2017 modify TB6612 library addition
 /* 
/*****************************************************************************/

#include <SparkFun_TB6612.h> 

char state = 'S';
char prevstate = 'A';
int velocity = 0;   
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started) 
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone  
  
  
//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
  const int BTState = 2;
  const int pinfrontLights = 4;    //Pin that activates the Front lights.
  const int pinbackLights  = 7;   //Pin that activates the Back lights.  
  const int buzzer = 6 ; //Buzzer / Speaker to Arduino Promini Pin 6
//  int state;
  int vSpeed1 = 0;     // Default main motor speed, from 0 to 255
  int vSpeed2 = 220;     // Default steering motor speed, from 0 to 255
//////////////////////////////TB6612///////////////////////////////////

//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

String readString;
/*****************************************************************/
  void setup() {
 
    pinMode(pinfrontLights, OUTPUT); 
   pinMode(pinbackLights, OUTPUT); 
    pinMode(buzzer, OUTPUT); 
    pinMode(BTState, INPUT); 
  
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
 // Initialize serial communication at 9600 bits per second:

 
    Serial.begin(9600);//9600 57600 19200 14400
}
 
void loop() {
 /***********************************Bluetooth**********************************************/
  //Stop car when connection lost or bluetooth disconnected
  //   if(digitalRead(BTState)==LOW) { 
//     state='S'; 
//     }
      if(Serial.available() > 0){ 
   timer1 = millis();   
    prevstate = state;
    state = Serial.read(); 
    //Change pin mode only if new command is different from previous.  
    
    if(state!=prevstate){
 
 
         
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {

  motor1.drive(vSpeed1,1);
   delay(10);
 //  motor1.drive(-255,1000);
  motor2.brake();
  delay(10);
   
   
//   move(1, vSpeed, 0); //drivemotor 1, speed, Forward
//  move(2, 0, 1); //steering motor 2, 0 speed, Right
  Serial.println("Forward-Straight");
        
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    if (state == 'G') {

  motor1.drive(vSpeed1,1);
  delay(10);
   motor2.drive(-vSpeed2,1);
 // motor2.brake();
  delay(10);

//  move(1, vSpeed, 0); //drivemotor 1, speed, Forward
//  move(2, 128, 1); //steering motor 2, 128 speed, Right
    
  Serial.println("Forward-Left");
     
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    if (state == 'I') {

  motor1.drive(vSpeed1,1);
  delay(10);
   motor2.drive(vSpeed2,1);
 // motor2.brake();
  delay(10);

//  move(1, vSpeed, 0); //drivemotor 1, speed, Forward
//  move(2, 0, 0); //steering motor 2, 0 speed, Right
  Serial.println("Forward-Right");
    }
  /***********************Backward straight****************************/
  //If state is equal with letter 'B', car will go backward
    if (state == 'B') {

   motor1.drive(-vSpeed1,1);
    delay(10);
//   motor2.drive(150,1000);
  motor2.brake();
  delay(10);
//  move(1, vSpeed, 1); //drivemotor 1, speed, backward
//  move(2, 0, 0); //steering motor 2, 0 speed, left
  
  Serial.println("Backward-Straight");    
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    if (state == 'H') {

     motor1.drive(-vSpeed1,1);
    delay(10);
   motor2.drive(-vSpeed2,1);
//  motor2.brake();
  delay(10);
 
  Serial.println("Backward-Left"); 
    }
    
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    if (state == 'J') {

    motor1.drive(-vSpeed1,1);
    delay(10);
   motor2.drive(vSpeed2,1);
//  motor2.brake();
  delay(10);

  Serial.println("Backward-Right"); 
        
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    if (state == 'L') {
     
   motor2.drive(-vSpeed2,1);
   delay(10);
  motor1.brake();
  delay(10);
  
  Serial.println("Turn-Left"); 
        
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    if (state == 'R') {

   motor2.drive(vSpeed2,1);
   delay(10);
  motor1.brake();
  delay(5);

  Serial.println("Turn-Right"); 
         
    }
  /************************front Lights*****************************/
  //If state is equal with letter 'W', turn front leds on 
  
    if (state == 'W') {
       digitalWrite(pinfrontLights, HIGH); 
       Serial.println("Frontlight  on");
        }
      if (state == 'w') {
         digitalWrite(pinfrontLights, LOW); 
         Serial.println("Frontlight  off"); 
        }
        
 /************************Back Lights*****************************/
 
    //If state is equal with letter 'U', turn front leds on 
    if (state == 'U') {
       digitalWrite(pinbackLights, HIGH); 
        Serial.println("Backlight  on"); 
        }
       if (state == 'u') {
         digitalWrite(pinbackLights, LOW); 
          Serial.println("Backlight  off"); 
        }
        
   
  /**********************Horn sound***************************/
  //If state is equal with letter 'V', play (or stop) horn sound

    if (state == 'V'){
        
         tone(buzzer, 1000);//Speaker on 
       Serial.println("Horn on"); 
      }
   else   if (state == 'v'){
         noTone(buzzer);    //Speaker off 
         Serial.println("Horn off"); 
      }
     
 /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    if (state == 'S' )
    {

    brake(motor1, motor2);
 /*
   motor1.brake();
   delay(10);
   motor2.brake();
   delay(10);
   */
 //    digitalWrite(pinfrontLights, LOW);
 //     digitalWrite(pinbackLights, LOW);
  //   noTone(buzzer);
   Serial.println("Standby");    
    }
    
  /************************Emergency*****************************/   
    
    /*    if ( state == 'D')  //Everything OFF )
    {

    brake(motor1, motor2);
 /*
   motor1.brake();
   delay(10);
   motor2.brake();
   delay(10);
   
     digitalWrite(pinfrontLights, LOW);
      digitalWrite(pinbackLights, LOW);
     noTone(buzzer);
   Serial.println("Emergency");    
    }
    */
   }//if(state!=prevstate)
    
       if(state =='q'){
          vSpeed1 = 220;  //Full velocity
          Serial.println(vSpeed1);
         delay(10); 
    }
   
    //  }//if(state!=prevstate)
      
  //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
      else   if((state >= 48) && (state <= 57))
          { 
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 28 changes the range from 0-9 to 0-255(L298N max speed)
            vSpeed1 = (state - 48)*25;       
          //  yellowCar.SetSpeed_4W(velocity);
          Serial.print("vSpeed1 = ");
         Serial.println(vSpeed1);
         delay(10);
         Serial.print("vSpeed2 = ");
         Serial.println(vSpeed2);
         delay(10);
          }

    else{
    timer0 = millis();  //Get the current time (millis since execution started).
    //Check if it has been 500ms since we received last command.
    if((timer0 - timer1)>500){  
      //More tan 500ms have passed since last command received, car is out of range.
      //Therefore stop the car and turn lights off.
      digitalWrite(pinfrontLights, LOW);
      digitalWrite(pinbackLights, LOW);
      void stop();
   delay(10);
    Serial.println("Out uf range");
    }
  }    
    }//if(Serial.available() > 0){     
      

}//void loop()end

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

 boolean inPin1 = LOW;
boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
