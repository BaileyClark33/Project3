//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "daylight_sensor.h"
#include "headlights.h"
#include "ignition.h"
#include "mbed.h"

/*We now expand our automobile control system to further include
 the windshield wiper subsystem. The wipers on most modern vehicles
 operate in four modes: (1) HI (high-speed); (2) LO (low-speed); (3)
 INT (intermittent or interval); and (4) OFF (off). An additional feature
 in this particular subsystem is a user display that
 indicates the wiper setting.

In the high-speed and low-speed modes, the wiper angle
periodically ramps up from 0 degrees to a maximum angle,
then ramps back down to 0 degrees, with no appreciable hesitation
at either end of travel. A typical maximum angle is 67 degrees
with the motor operating at 40 revolutions per minute (rpm) for
high-speed mode and 30 rpm for low-speed mode.

Intermittent mode is identical to low-speed mode with the
 following exception: whenever the wiper returns to the 0-degree position,
 it hesitates for a driver-selectable delay time before resuming motion.
 Typical delay times produce INT cycles with periods of 3, 6, or 8 seconds.
 Figure 1 (not drawn to scale) illustrates the wiper speed trajectory
  in 3-second INT mode. Figure 2 (also not drawn to scale) illustrates
  the wiper angle trajectory in that same mode.
*/

//=====[Declaration of private defines]========================================

#define DUTY_MIN 0.065 // Duty cycle is pulse_width/period
#define DUTY_MAX 0.85
#define DUTY_STOP 0.065
#define PERIOD 0.02 // Units of period is seconds
#define HIGH_PERIOD 0.04
#define LOW_PERIOD 0.02
#define INT_PERIOD 0.02
#define 

//=====[Declaration of private data types]=====================================

PwmOut servo(PF_9);

typedef enum {
  WIPERS_OFF,
  WIPERS_INT,
  WIPERS_HI,
  WIPERS_LOW
} windshield_state_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

windshield_state_t wiperState;

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

AnalogIn wiperSelect(A0);

int target;

//=====[Declarations (prototypes) of private functions]========================

void windshieldRun();
void selectorUpdate();
void wipersHi();
void wipersLow();
void wipersInt();
void wipersOff();
void wipersRun( float period );

//=====[Implementations of public functions]===================================

void windshieldInit() {
  servo.period(PERIOD);
  servo.write(DUTY_MIN); // start at 0
  target = 0;
}

void windshieldUpdate() { // ingitionRun calls this
  selectorUpdate();
  windshieldRun();
}

void wipersReturn() {
  if (servo.read() > 2) {
    switch (wiperState) {
    case WIPERS_OFF:
      wipersOff();
      break;
    case WIPERS_HI:
      wipersHi();
      break;
    case WIPERS_LOW:
      wipersLow();
      break;
    case WIPERS_INT:
      wipersInt();
      break;
    default:
      wiperState = WIPERS_OFF;
    }
  } else {
    servo.write(0.025);
  }
}

//=====[Implementations of private functions]==================================

void windshieldRun() {
  if (!ignitionRead()) {
    wiperState = WIPERS_OFF;
  }
  switch (wiperState) {

  case WIPERS_HI:
    wipersHi();
    break;
  case WIPERS_LOW:
    wipersLow();
    break;
  case WIPERS_INT:
    wipersInt();
    break;
  default:
    case WIPERS_OFF:
    wipersOff();
    wiperState = WIPERS_OFF;
    break;
    
  }
}

void selectorUpdate() {
  float num = wiperSelect.read();
  if (num >= 0.8) {
    wiperState = WIPERS_HI;
  } else if (0.5 < num && num < 0.8) {
    wiperState = WIPERS_LOW;
  } else if (0.2 < num && num < 0.5) {
    wiperState = WIPERS_INT;
  } else {
    wiperState = WIPERS_OFF;
  }
}

void wipersHi() {
    uartUsb.write("Wiper mode: Hi\n", 16);
    //wipersRun( HIPERIOD );
}

void wipersLow() {
    uartUsb.write("Wiper mode: Intermittent\n", 28);
    //wipersRun( LOWPERIOD );
}

void wipersInt() {
    uartUsb.write("Wiper mode: Low\n", 17);
    //wipersRun( INTPERIOD );
}

void wipersOff() { 
    uartUsb.write("Wiper mode: Intermittent\n", 28);
    wipersReturn(); 
}

void wipersRun( float period ) {
    if (target == 0) {
        servo.period(period);
        servo.write(0.5 / period);
        if (servo.read() < 2) {
            target = 180;
        }
    } else if (target == 180) {
        servo.period(period);
        servo.write(2.5 / period);
        if (servo.read() > 178) {
            target = 0;
        }
    }
}

//=====[Main function, the program entry point after power on or reset]========

/*
If the engine is running, and the user selects HI, LO, INT, or OFF,
run the wipers in the appropriate mode, with the typical parameter values,
as described above. Read the desired delay time for INT mode from the
intermittent delay time selector. Do not run the wipers if the engine
is not running.
display the selected mode, including the delay time selection
(SHORT, MEDIUM, or LONG) for intermittent mode.
If the wiper mode selector is turned to OFF, or the engine is turned off, then
if the wiper is moving, in any mode, complete the current cycle and
 return the wipers to 0 degrees;
if the wiper is hesitating in INT mode, remain stationary.

*/
