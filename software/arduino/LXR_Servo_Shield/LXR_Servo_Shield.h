/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the library for controlling the LXRobotics Servo Shield for controlling up to 32 servos
 * @file LXR_Servo_Shield.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LXR_SERVO_SHIELD_H_
#define LXR_SERVO_SHIELD_H_

/* INCLUDES */
 
#include "Arduino.h"

/* DEFINES */

//#define _DEBUG_ENABLED

#define REG_LED_0           (0x08)  // LED0_OFF_L
#define REG_LED_1           (REG_LED_0+1*4)
#define REG_LED_2           (REG_LED_0+2*4)
#define REG_LED_3           (REG_LED_0+3*4)
#define REG_LED_4           (REG_LED_0+4*4)
#define REG_LED_5           (REG_LED_0+5*4)
#define REG_LED_6           (REG_LED_0+6*4)
#define REG_LED_7           (REG_LED_0+7*4)
#define REG_LED_8           (REG_LED_0+8*4)
#define REG_LED_9           (REG_LED_0+9*4)
#define REG_LED_10          (REG_LED_0+10*4)
#define REG_LED_11          (REG_LED_0+11*4)
#define REG_LED_12          (REG_LED_0+12*4)
#define REG_LED_13          (REG_LED_0+13*4)
#define REG_LED_14          (REG_LED_0+14*4)
#define REG_LED_15          (REG_LED_0+15*4)

/* GLOBAL CONSTANTS */

// NO JUMPERS SET
static byte const IC1_DEV_ADDR_NO_JUMPERS_SET = 0x40;
static byte const IC2_DEV_ADDR_NO_JUMPERS_SET = 0x60;
// ALL JUMPERS SET
static byte const IC1_DEV_ADDR_ALL_JUMPERS_SET = 0x5F;
static byte const IC2_DEV_ADDR_ALL_JUMPERS_SET = 0x7F;
// and there are 32 other combinations possibble ... (depending on how the address jumpers are set)

/* TYPEDEFS */

typedef enum
{
   SERVO_1 = 0,
   SERVO_2 = 1,
   SERVO_3 = 2,
   SERVO_4 = 3,
   SERVO_5 = 4,
   SERVO_6 = 5,
   SERVO_7 = 6,
   SERVO_8 = 7,
   SERVO_9 = 8,
   SERVO_10 = 9,
   SERVO_11 = 10,
   SERVO_12 = 11,
   SERVO_13 = 12,
   SERVO_14 = 13,
   SERVO_15 = 14,
   SERVO_16 = 15,
   SERVO_17 = 16,
   SERVO_18 = 17,
   SERVO_19 = 18,
   SERVO_20 = 19,
   SERVO_21 = 20,
   SERVO_22 = 21,
   SERVO_23 = 22,
   SERVO_24 = 23,
   SERVO_25 = 24,
   SERVO_26 = 25,
   SERVO_27 = 26,
   SERVO_28 = 27,
   SERVO_29 = 28,
   SERVO_30 = 29,
   SERVO_31 = 30,
   SERVO_32 = 31
} E_SERVO_SELECT;

typedef enum {IC1 = 0, IC2 = 1} E_IC_SELECT;

/* PROTOTYPES */

class LXR_Servo_Shield 
{
public:
  /**
   * @brief Constructor
   * @param ic_1_dev_address i2c address of the pwm ic1 (selectable by jumpers)
   * @param ic_2_dev_address i2c address of the pwm ic2 (selectable by jumpers)
   * @param use_oe_enable_pins make use of the output enable pins
   */
  LXR_Servo_Shield(byte const ic_1_dev_addr, byte const ic_2_dev_addr, boolean const use_oe_enable_pins);
  
  /**
   * @brief initializes the servo shield
   */
  void begin();
  
  /** 
   * @brief sets the pins OE_SC1 and OE_SC2 to LOW, therefor the pwm outputs of all servos are enabled
   * @return true in case of success, false in case of failure (use_oe_enable_pins in ctor must be set to true + jumpers SC1_OE_ENABLE and SC2_OE_ENABLE) must be set)
   */
  boolean enable_pwm_outputs();

  /** 
   * @brief sets the pins OE_SC1 and OE_SC2 to HIGH, therefor the pwm outputs of all servos are disabled
   * @return true in case of success, false in case of failure (use_oe_enable_pins in ctor must be set to true + jumpers SC1_OE_ENABLE and SC2_OE_ENABLE) must be set)
   */  
  boolean disable_pwm_outputs();
  
  /** 
   * @brief sets the servo output selected by sel to have a pulse with pulse_duration_us microseconds - ATTENTION: BE CAREFUL THAT THE SET PULSE DURATION IS WITHIN THE SERVO SPECIFICATION of 1000 to 2000 us - OPERATING YOUR SERVO OUTIDE OF THIS SPECIFICATION CAN DESTROY OR DAMAGE YOUR SERVO !
   */
  void set_servo_pulse_duration(E_SERVO_SELECT const sel, int const pulse_duration_us);
  
private:
  boolean const m_use_oe_enable_pins;
  byte m_ic_dev_addr[2];
   
#ifdef _DEBUG_ENABLED  
  /** 
   * @brief read a byte from one of the two pwm ics (reg describes the reg address)
   */
  byte read_byte(E_IC_SELECT const sel, byte const reg);
#endif
  
  /** 
   * @brief writes a byte to one of the two pwm ics (reg describes the reg address)
   */
  void write_byte(E_IC_SELECT const sel, byte const reg, byte const data);
  
  /**
   * @brief set the servo pwm value
   */
  void set_servo_pwm(E_IC_SELECT const ic_sel, byte const led_reg, int const pulse_duration_us);
};

#endif
