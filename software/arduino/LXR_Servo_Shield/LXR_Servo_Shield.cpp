/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the library for controlling the LXRobotics Servo Shield for controlling up to 32 servos
 * @file LXR_Servo_Shield.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
/* INCLUDES */

#include "LXR_Servo_Shield.h"
#include "Wire.h"

/* DEFINES */

// REG ADDRESSES
#define REG_MODE1           (0x00)
#define REG_PRE_SCALE       (0xFE)

// BITMAPS
#define MODE1_AI_bm         (1<<5)
#define MODE1_SLEEP_bm      (1<<4)
#define MODE1_ALLCALL_bm    (1<<0)

/* TYPEDEFS */

typedef struct
{
  E_IC_SELECT ic_sel;
  byte led_reg;
} s_servo_map;
  

/* GLOBAL CONSTANTS */

static int const OE_SC1_PIN = 9; // D9
static int const OE_SC2_PIN = 8; // D8
  
static s_servo_map const m_servo_map[] =
{
  {IC1, REG_LED_0}, // SERVO_1
  {IC1, REG_LED_1}, // SERVO_2
  {IC1, REG_LED_2}, // SERVO_3
  {IC1, REG_LED_3}, // SERVO_4
  {IC1, REG_LED_4}, // SERVO_5
  {IC1, REG_LED_5}, // SERVO_6
  {IC1, REG_LED_6}, // SERVO_7
  {IC1, REG_LED_7}, // SERVO_8
  {IC1, REG_LED_8}, // SERVO_9
  {IC1, REG_LED_9}, // SERVO_10
  {IC1, REG_LED_10}, // SERVO_11
  {IC1, REG_LED_11}, // SERVO_12
  {IC1, REG_LED_12}, // SERVO_13
  {IC1, REG_LED_13}, // SERVO_14
  {IC1, REG_LED_14}, // SERVO_15
  {IC1, REG_LED_15}, // SERVO_16
  {IC2, REG_LED_0}, // SERVO_17
  {IC2, REG_LED_1}, // SERVO_18
  {IC2, REG_LED_2}, // SERVO_19
  {IC2, REG_LED_3}, // SERVO_20
  {IC2, REG_LED_4}, // SERVO_21
  {IC2, REG_LED_5}, // SERVO_22
  {IC2, REG_LED_6}, // SERVO_23
  {IC2, REG_LED_7}, // SERVO_24
  {IC2, REG_LED_8}, // SERVO_25
  {IC2, REG_LED_9}, // SERVO_26
  {IC2, REG_LED_10}, // SERVO_27
  {IC2, REG_LED_11}, // SERVO_28
  {IC2, REG_LED_12}, // SERVO_29
  {IC2, REG_LED_13}, // SERVO_30
  {IC2, REG_LED_14}, // SERVO_31
  {IC2, REG_LED_15} // SERVO_32
};

/* FUNCTIONS */

/**
 * @brief Constructor initializes the servo shield
 * @param ic_1_dev_address i2c address of the pwm ic1 (selectable by jumpers)
 * @param ic_2_dev_address i2c address of the pwm ic2 (selectable by jumpers)
 * @param use_oe_enable_pins make use of the output enable pins
 */
LXR_Servo_Shield::LXR_Servo_Shield(byte const ic_1_dev_addr, byte const ic_2_dev_addr, boolean const use_oe_enable_pins) : m_use_oe_enable_pins(use_oe_enable_pins)
{
  // assign i2c addresses
  m_ic_dev_addr[IC1] = ic_1_dev_addr;
  m_ic_dev_addr[IC2] = ic_2_dev_addr;
}

/**
 * @brief initializes the servo shield
 */
void LXR_Servo_Shield::begin()
{
  // initialize wire library
  Wire.begin();
  // setup oe enable pins
  if(m_use_oe_enable_pins)
  {
    pinMode(OE_SC1_PIN, OUTPUT);
    pinMode(OE_SC2_PIN, OUTPUT);
    disable_pwm_outputs();
  }
  // write default configuration to register MODE1
  write_byte(IC1, REG_MODE1, (MODE1_SLEEP_bm | MODE1_ALLCALL_bm));
  write_byte(IC2, REG_MODE1, (MODE1_SLEEP_bm | MODE1_ALLCALL_bm));
  // set pwm frequency = 50 Hz = 20 ms, prescale = round(25MHz/(4096*50)) - 1 = 121
  write_byte(IC1, REG_PRE_SCALE, 121);
  write_byte(IC2, REG_PRE_SCALE, 121);
  // deactivate sleep mode and activate auto increment mode
  write_byte(IC1, REG_MODE1, (MODE1_AI_bm | MODE1_ALLCALL_bm));
  write_byte(IC2, REG_MODE1, (MODE1_AI_bm | MODE1_ALLCALL_bm));  
  // wait a bit to get the oscillator up and running
  delay(100);
  
#ifdef _DEBUG_ENABLED
  // activate serial for debug purposes
  Serial.begin(115200);
  byte buf[32], length;
  length = sprintf((char*)(buf), "IC1.MODE1 = 0x%x\n", read_byte(IC1, REG_MODE1));
  Serial.write(buf, length);
  length = sprintf((char*)(buf), "IC2.MODE1 = 0x%x\n", read_byte(IC2, REG_MODE1));
  Serial.write(buf, length);
  length = sprintf((char*)(buf), "IC1.PRE_SCALE = 0x%x\n", read_byte(IC1, REG_PRE_SCALE));
  Serial.write(buf, length);
  length = sprintf((char*)(buf), "IC2.PRE_SCALE = 0x%x\n", read_byte(IC2, REG_PRE_SCALE));
  Serial.write(buf, length);
#endif  
}

/** 
 * @brief sets the pins OE_SC1 and OE_SC2 to LOW, therefor the pwm outputs of all servos are enabled
 * @return true in case of success, false in case of failure (use_oe_enable_pins in ctor must be set to true + jumpers SC1_OE_ENABLE and SC2_OE_ENABLE) must be set)
 */
boolean LXR_Servo_Shield::enable_pwm_outputs()
{
  if(m_use_oe_enable_pins)
  {
    digitalWrite(OE_SC1_PIN, LOW);
    digitalWrite(OE_SC2_PIN, LOW);
    return true;
  }
  else
  {
    return false;
  }
}

/** 
 * @brief sets the pins OE_SC1 and OE_SC2 to HIGH, therefor the pwm outputs of all servos are disabled
 * @return true in case of success, false in case of failure (use_oe_enable_pins in ctor must be set to true + jumpers SC1_OE_ENABLE and SC2_OE_ENABLE) must be set)
 */  
boolean LXR_Servo_Shield::disable_pwm_outputs()
{
  if(m_use_oe_enable_pins)
  {
    digitalWrite(OE_SC1_PIN, HIGH);
    digitalWrite(OE_SC2_PIN, HIGH);
    return true;
  }
  else
  {
    return false;
  }
}

/** 
 * @brief sets the servo output selected by sel to have a pulse with pulse_duration_us microseconds - ATTENTION: BE CAREFUL THAT THE SET PULSE DURATION IS WITHIN THE SERVO SPECIFICATION of 1000 to 2000 us - OPERATING YOUR SERVO OUTIDE OF THIS SPECIFICATION CAN DESTROY OR DAMAGE YOUR SERVO !
 */
void LXR_Servo_Shield::set_servo_pulse_duration(E_SERVO_SELECT const sel, int const pulse_duration_us)
{
  set_servo_pwm(m_servo_map[sel].ic_sel, m_servo_map[sel].led_reg, pulse_duration_us);
}

#ifdef _DEBUG_ENABLED  
/** 
 * @brief read a byte from one of the two pwm ics (reg describes the reg address)
 */
byte LXR_Servo_Shield::read_byte(E_IC_SELECT const sel, byte const reg)
{
  Wire.beginTransmission(m_ic_dev_addr[sel]);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(m_ic_dev_addr[sel], (byte)(1));
  return Wire.read();
}
#endif

/** 
 * @brief writes a byte to one of the two pwm ics (reg describes the reg address)
 */
void LXR_Servo_Shield::write_byte(E_IC_SELECT const sel, byte const reg, byte const data)
{
  Wire.beginTransmission(m_ic_dev_addr[sel]);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 * @brief set the servo pwm value
 */
void LXR_Servo_Shield::set_servo_pwm(E_IC_SELECT const ic_sel, byte const led_reg, int const pulse_duration_us)
{
  // 20 ms / 4096 = 4.8828 us = 1 Timertick => 1 us = 1/4.883 Timerticks
  int const timer_ticks = min(((uint32_t)(pulse_duration_us) * 100) / 488, 4095);
    
  Wire.beginTransmission(m_ic_dev_addr[ic_sel]);
  Wire.write(led_reg);

  // write LEDx_OFF_L
  Wire.write((byte)(timer_ticks & 0xFF));
  // write LEDx_OFF_H
  Wire.write((byte)((timer_ticks >> 8) & 0xFF));

  Wire.endTransmission();
  
#ifdef _DEBUG_ENABLED
  byte buf[32], length;
  length = sprintf((char*)(buf), "ICx.LEDx_ON_L = 0x%x\n", read_byte(ic_sel, led_reg));
  Serial.write(buf, length);
  length = sprintf((char*)(buf), "ICx.LEDx_ON_H = 0x%x\n", read_byte(ic_sel, led_reg+1));
  Serial.write(buf, length);
  length = sprintf((char*)(buf), "ICx.LEDx_OFF_L = 0x%x\n", read_byte(ic_sel, led_reg+2));
  Serial.write(buf, length);  
  length = sprintf((char*)(buf), "ICx.LEDx_OFF_H = 0x%x\n", read_byte(ic_sel, led_reg+3));
  Serial.write(buf, length);  
#endif  
}
