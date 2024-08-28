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
// he attach() function also initializes the timer for PWM control.
void loop(void){
  sensor_analog = analogRead(sensor_pin);
  // - `float(sensor_analog)`: Converts the integer `sensor_analog` value to a floating-point number for precise division.
  // - `sensor_analog / 4095.00`: Normalizes the sensor value to a range between 0.0 and 1.0. (Assuming a 12-bit ADC, which has a maximum value of 4095.)
  // - `(float(sensor_analog) / 4095.00) * 100`: Converts the normalized value to a percentage.
  // - `100.0 - ...`: Subtracts this value from 100 to invert it, assuming higher analog values correspond to drier conditions (less moisture).
  // - `int(...)`: Converts the floating-point percentage back to an integer, storing it in `_moisture`.
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

