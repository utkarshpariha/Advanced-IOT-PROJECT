#define REMOTEXY_MODE__ESP32CORE_WIFI_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>


#define REMOTEXY_WIFI_SSID "Missquery"
#define REMOTEXY_WIFI_PASSWORD "Missquery@27"
#define REMOTEXY_SERVER_PORT 6377
#define REMOTEXY_ACCESS_PASSWORD "Missquery@27"


 
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 36 bytes
  { 255,3,0,0,0,29,0,16,1,0,2,0,5,6,22,11,2,26,31,31,
  79,78,0,79,70,70,0,5,8,60,28,30,30,2,26,31 };
  

struct {

  uint8_t switch_1;  
  int8_t joystick_1_x;   
  int8_t joystick_1_y;

    
  uint8_t connect_flag;  

} RemoteXY;
#pragma pack(pop)


#define ENA   4     
#define IN_1  0     
#define IN_2  2     
#define IN_3  12   
#define IN_4  13    
#define ENB   15   
           
int speedCar = 150;
int speed_low = 60;

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(115200);

  pinMode(ENA, OUTPUT); 
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(ENB, OUTPUT); 
}

void loop() 
{ 
  RemoteXY_Handler ();
  if((Input.joystick_x<10 || Input.joystick_x>-10) && (RemoteXY.joystick_y<10 || Input.joystick_y>-10)){
    stop();
  }
  if(Input.joystick_x<-60){
    goLeft();
  }
    if(Input.joystick_x>60){
    goRight();
  }
    if(Input.joystick_y>60){
    goForword();
  }
    if(Input.joystick_y<-60){
    goBack();
  }
  if(Input.slider>=0 && Input.slider<=10){
    speedCar=100;
  }
    if(Input.slider>=11 && Input.slider<=20){
    speedCar=120;
  }
    if(Input.slider>=21 && Input.slider<=30){
    speedCar=140;
  }
    if(Input.slider>=31 && Input.slider<=40){
    speedCar=160;
  }
    if(Input.slider>=41 && Input.slider<=50){
    speedCar=180;
  }
    if(Input.slider>=51 && Input.slider<=60){
    speedCar=200;
  }
    if(Input.slider>=61 && Input.slider<=70){
    speedCar=215;
  }
    if(Input.slider>=71 && Input.slider<=80){
    speedCar=230;
  }
    if(Input.slider>=81 && Input.slider<=90){
    speedCar=240;
  }
    if(Input.slider>=91 && Input.slider<=100){
    speedCar=255;
  }
}

void goForword(){ 

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goBack(){ 

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goLeft(){

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void goRight(){ 

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void stop(){  

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}
