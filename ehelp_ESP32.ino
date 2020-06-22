

/* To DO
-- Update servo library for none esp 32
-- Update anaolg in level
-  Check signal quality for switch may need pull up resistor.
-- update pins
-- Remove newmap function when going with MO board
-- Tune Throttle for useful range
*/

//****************************************************
//** DEFINE KEY SETTINGS, INSTANCES AND PINS HERE ****
//****************************************************
// Servo for ESC
#include <ESP32_Servo.h>  // https://www.youtube.com/watch?v=_WqfNyE_pt8
Servo ESC;  // ESC

int ESC_pin = 13;  // Working on ESP32. Additional Working pins for Servo out 14, 15 on ESP32
int ThrottlePin = A0;
int Power_Switch = A1; 
float Vs = 3.3;  //This is the supply voltage of board
int ThrottleMS;  // Throttle output in milli seconds for ESC

int Switch_val = 0;

//****************************************************
//********* RUN SETUP CODE HERE - RUNS ONCE **********
//****************************************************
void setup() {
  Serial.begin(9600);  //Start the serial connection with the computer to view the result open the serial monitor 

  // ESC Servo setup code*****************************************************************
  ESC.attach(ESC_pin, 1000, 2000);  // attaches the servo ESCpin to a pwm pin and sets conrol range 

 pinMode(Power_Switch, INPUT);    // sets the digital pin as input

} // END OF SETUP

//****************************************************
//******* RUN Main CODE HERE - RUNS REPEATEDLY *******
//****************************************************

void loop() {
  Switch_val = analogRead(Power_Switch);
  //Serial.println(Switch_val);
  
  if (Switch_val < 4095) {
      ThrottleMS = 1000;
      ESC.writeMicroseconds(ThrottleMS);    // uses throttle from controller
  } else {
      ThrottleMS = New_Map(analogRead(ThrottlePin), 400, 2800, 1110, 2000);  // 1110 was used as low in Open PPG
      if (ThrottleMS > 2000) { ThrottleMS = 2000;}
      if (ThrottleMS < 1110) { ThrottleMS = 1110;}
      ESC.writeMicroseconds(ThrottleMS);    // uses throttle from controller
  }// End if else
  
  //Serial.print("Raw Pin in: "); Serial.print(analogRead(ThrottlePin)); Serial.print(",  ThrottleMS: "); Serial.println(ThrottleMS); 
  //Serial.print("throttle: "); Serial.println(ThrottleMS);  // Debug line
  
  } // End Loop

//******* Start New Map Funciton OUTPUT for ESP32 ******************************
  long New_Map(long x, long in_min, long in_max, long out_min, long out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  } // end map
//******* End New Map Funciton OUTPUT ******************************
