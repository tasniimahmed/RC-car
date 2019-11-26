#include <NewPing.h>

# include "NewPing.h"

int Motor_R_Enable=11;
int Motor_R_Forward=13;
int Motor_R_Reverse=12;

int Motor_L_Enable=6;
int Motor_L_Forward=7;
int Motor_L_Reverse=8;

int trigPin=4;   
int echoPin=3;
#define required_distance 25
#define sensorLeft 5
#define sensorCenter 10
#define sensorRight 9
int x,y,z;
NewPing sonar(trigPin ,echoPin ,required_distance ) ;
float distance ;

char input;

void setup() {
  
  Serial.begin(9600);
  pinMode(Motor_R_Enable,OUTPUT);
  pinMode(Motor_R_Forward,OUTPUT);
  pinMode(Motor_R_Reverse,OUTPUT);
  pinMode(Motor_L_Enable,OUTPUT);
  pinMode(Motor_L_Forward,OUTPUT);
  pinMode(Motor_L_Reverse,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(sensorLeft,INPUT);
pinMode(sensorCenter,INPUT);
pinMode(sensorRight,INPUT);


}

void forward(){
        analogWrite(Motor_L_Enable,100);
        digitalWrite(Motor_L_Forward,HIGH);
        digitalWrite(Motor_L_Reverse,LOW);
        analogWrite(Motor_R_Enable,100);
        digitalWrite(Motor_R_Forward,HIGH);
        digitalWrite(Motor_R_Reverse,LOW);
}

void backward(){
        analogWrite(Motor_L_Enable,150);
        digitalWrite(Motor_L_Forward,LOW);
        digitalWrite(Motor_L_Reverse,HIGH);
        analogWrite(Motor_R_Enable,150);
        digitalWrite(Motor_R_Forward,LOW);
        digitalWrite(Motor_R_Reverse,HIGH);
}

void brake(){
        analogWrite(Motor_L_Enable,150);
        digitalWrite(Motor_L_Forward,LOW);
        digitalWrite(Motor_L_Reverse,LOW);
        analogWrite(Motor_R_Enable,150);
        digitalWrite(Motor_R_Forward,LOW);
        digitalWrite(Motor_R_Reverse,LOW);
}

void left (){
        analogWrite(Motor_L_Enable,150);
        digitalWrite(Motor_L_Forward,LOW);
        digitalWrite(Motor_L_Reverse,LOW);
        analogWrite(Motor_R_Enable,150);
        digitalWrite(Motor_R_Forward,HIGH);
        digitalWrite(Motor_R_Reverse,LOW);
}

void right (){
        analogWrite(Motor_L_Enable,150);
        digitalWrite(Motor_L_Forward,HIGH);
        digitalWrite(Motor_L_Reverse,LOW);
        analogWrite(Motor_R_Enable,50);
        digitalWrite(Motor_R_Forward,LOW);
        digitalWrite(Motor_R_Reverse,HIGH);
}
void rightwall (){
        analogWrite(Motor_L_Enable,150);
        digitalWrite(Motor_L_Forward,HIGH);
        digitalWrite(Motor_L_Reverse,LOW);
        analogWrite(Motor_R_Enable,100);
        digitalWrite(Motor_R_Forward,LOW);
        digitalWrite(Motor_R_Reverse,HIGH);
}

void track (){
  //lw mashtaghlsh yb2a n7ot hena bardo code el sensor tany
  x=digitalRead(sensorLeft);
  y=digitalRead(sensorCenter);
  z=digitalRead(sensorRight);
   if ( distance <=20 && distance != 0 && z==0 )
     {
         backward();
         delay (300);
         rightwall();
         delay(400);
         forward();
         delay(500);

    }
  else if ( distance <=20 && distance != 0 && x==0)
    {
         backward();
         delay (300);
         left();
         delay(700);
         forward();
         delay(500);
    }    
  else { 
               if(x & !y & z)
           {
          //move forward
            forward();
           }
          
          else if(!x & y & z)
           {
            //move left
              left(); 
           }
          
         if(x & y & !z)
           {
           //move right 
             right();
           } 
        
        else if(!x & !y & !z)
          {
             forward();
          }   
  }//else
}

void loop(){
 if(Serial.available() > 0){
    input = Serial.read(); 
}
switch (input){
  case 'F': 
  distance=sonar.ping_cm();
if ( distance <10 && distance != 0){
  backward();
  delay (300);
  left();
  delay(600);
  forward();
} else{
  forward();
  break;
}
  case 'L': distance=sonar.ping_cm();
if ( distance <10 && distance != 0){
  backward();
  delay (300);
  left();
  delay(600);
  forward();
} else{
  left();
  break;
}
  case 'R' : distance=sonar.ping_cm();
if ( distance <10 && distance != 0){
  backward();
  delay (300);
  left();
  delay(600);
  forward();
} else{
  right();
  break;
}
  case 'B' : backward(); break;
  case 'W' : brake(); break;
  case 'U':
  Serial.print(input);
  track(); break; 
}


}
