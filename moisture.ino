#include <Servo.h>

Servo servo1;

int pos;

int _moisture,sensor_analog;
int sensor_pin = A1;

void setup(void){
  pinMode(sensor_pin, INPUT);
  Serial.begin(115200);
  servo1.attach(A0);     
}

void loop(void){
  sensor_analog = analogRead(sensor_pin);
  _moisture = int(100.0-(float(sensor_analog) / 4095.00) * 100);
  Serial.print("Moisture = ");
  Serial.print(_moisture);  
  Serial.print("%");
  delay(200);              
  if(_moisture<85){
    for(pos=15;pos<90;pos++){
    servo1.write(pos);
    }}
  else if (_moisture>=85){
    for(pos=90;pos>15;pos--){
    servo1.write(pos);
    }
    }
} 

