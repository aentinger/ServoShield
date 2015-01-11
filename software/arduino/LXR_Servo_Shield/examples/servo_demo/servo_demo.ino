/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch demonstrates how to use the LXRobotics Servo Shield Library to control up to 32 servos
 * @file servo_demo.ino
 */

/* INCLUDES */

#include <Serial> // including Serial is only necessary if the define _DEBUG_ENABLED in LXR_Servo_Shield.h is uncommented
#include "Wire.h" // dont forget to include Wire.h ! 
#include "LXR_Servo_Shield.h"

/* GLOBLAL VARIABLES */

LXR_Servo_Shield servo(IC1_DEV_ADDR_ALL_JUMPERS_SET, IC2_DEV_ADDR_ALL_JUMPERS_SET, true);

/* FUNCTIONS */
 
void setup() 
{
  // init servo shield
  servo.begin();
  // enable the pwm outputs
  servo.enable_pwm_outputs();
}
 
void loop() 
{
  for(int i=1000; i<2000; i+=50)
  {
   servo.set_servo_pulse_duration(SERVO_1, i);
   //servo.set_servo_pulse_duration(SERVO_2, i);
   //servo.set_servo_pulse_duration(SERVO_3, i);
   //servo.set_servo_pulse_duration(SERVO_4, i);
   //servo.set_servo_pulse_duration(SERVO_5, i);
   //servo.set_servo_pulse_duration(SERVO_6, i);
   //servo.set_servo_pulse_duration(SERVO_7, i);
   //servo.set_servo_pulse_duration(SERVO_8, i);
   //servo.set_servo_pulse_duration(SERVO_9, i);
   //servo.set_servo_pulse_duration(SERVO_10, i);
   //servo.set_servo_pulse_duration(SERVO_11, i);
   //servo.set_servo_pulse_duration(SERVO_12, i);
   //servo.set_servo_pulse_duration(SERVO_13, i);
   //servo.set_servo_pulse_duration(SERVO_14, i);
   //servo.set_servo_pulse_duration(SERVO_15, i);
   //servo.set_servo_pulse_duration(SERVO_16, i);
   //servo.set_servo_pulse_duration(SERVO_17, i);
   //servo.set_servo_pulse_duration(SERVO_18, i);
   //servo.set_servo_pulse_duration(SERVO_19, i);
   //servo.set_servo_pulse_duration(SERVO_20, i);
   //servo.set_servo_pulse_duration(SERVO_21, i);
   //servo.set_servo_pulse_duration(SERVO_22, i);
   //servo.set_servo_pulse_duration(SERVO_23, i);
   //servo.set_servo_pulse_duration(SERVO_24, i);
   //servo.set_servo_pulse_duration(SERVO_25, i);
   //servo.set_servo_pulse_duration(SERVO_26, i);
   //servo.set_servo_pulse_duration(SERVO_27, i);
   //servo.set_servo_pulse_duration(SERVO_28, i);
   //servo.set_servo_pulse_duration(SERVO_29, i);
   //servo.set_servo_pulse_duration(SERVO_30, i);
   //servo.set_servo_pulse_duration(SERVO_31, i);
   //servo.set_servo_pulse_duration(SERVO_32, i);
   delay(50); 
  }
}

