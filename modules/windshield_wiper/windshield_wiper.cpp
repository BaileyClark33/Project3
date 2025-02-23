//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "ignition.h"
#include "mbed.h"
#include "display.h"
#include "windshield_wiper.h"
#include "servo.h"

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

//=====[Declaration of private data types]=====================================

PwmOut servo(PF_9);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

AnalogIn wiperSelect(A0);
AnalogIn delaySelect(A1);

int delayState;
windshield_state_t wiperState;
int wiperUpdateCounter = 0;

//=====[Declarations (prototypes) of private functions]========================

void windshieldRun();
void selectorUpdate();
void delaySelectorUpdate();
void wipersHi();
void wipersLow();
void wipersInt();
void wipersOff();


//=====[Implementations of public functions]===================================

void windshieldInit() {
  servo.period(PERIOD);
  servo.write(DUTY_MIN); // start at 0
}

void windshieldUpdate() { // ingitionRun calls this
  selectorUpdate();
  delaySelectorUpdate();
  windshieldRun();
}

//=====[Implementations of private functions]==================================

void windshieldRun() {
  if (!ignitionRead()) {
    wipersOff();
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

void delaySelectorUpdate() {
  float num = delaySelect.read();

  if (num >= .06) {
    delayState = 8000;
  } else if (num > .03 && num <= .06) {
    delayState = 6000;
  } else {
    delayState = 3000;
  }
}

void wipersHi() {
    wiperUpdateCounter++;
    if (wiperUpdateCounter == 0) {
         servoUpdate(SERVO_RIGHT);
    }
    else if (wiperUpdateCounter == 28) {
    servoUpdate(SERVO_LEFT);
    }
    else if (wiperUpdateCounter == 56) {
    servoUpdate(SERVO_STOP);
    }
    else if (wiperUpdateCounter == 300) {
        wiperUpdateCounter = 0;
    }
}

void wipersLow() {
    wiperUpdateCounter++;
    if (wiperUpdateCounter == 0) {
         servoUpdate(SERVO_RIGHT);
    }
    else if (wiperUpdateCounter == 37) {
    servoUpdate(SERVO_LEFT);
    }
    else if (wiperUpdateCounter == 74) {
        servoUpdate(SERVO_STOP);
    }
    else if (wiperUpdateCounter == 300) {
        wiperUpdateCounter = 0;
    }
}

void wipersInt() {
    wiperUpdateCounter++;
    switch (delayState) {
        case 3000:
        wipersLow();
        break;
        case 6000:
        if (wiperUpdateCounter == 0) {
            servoUpdate(SERVO_RIGHT);
        }
        else if (wiperUpdateCounter == 37) {
        servoUpdate(SERVO_LEFT);
        }
        else if (wiperUpdateCounter == 74) {
            servoUpdate(SERVO_STOP);
        }
        else if (wiperUpdateCounter == 600) {
            wiperUpdateCounter = 0;
        }
        break;
        case 8000:
        if (wiperUpdateCounter == 0) {
            servoUpdate(SERVO_RIGHT);
        }
        else if (wiperUpdateCounter == 37) {
        servoUpdate(SERVO_LEFT);
        }
        else if (wiperUpdateCounter == 74) {
            servoUpdate(SERVO_STOP);
        }
        else if (wiperUpdateCounter == 800) {
            wiperUpdateCounter = 0;
        }
        break;
        default:
        break;
    }
}

void wipersOff() { 
    wiperUpdateCounter++;
    if (wiperUpdateCounter == 40) {
        servoUpdate(SERVO_STOP);
    }
}

windshield_state_t getWiperState() {
    return wiperState;
}

int getDelayState() {
    return delayState;
}
