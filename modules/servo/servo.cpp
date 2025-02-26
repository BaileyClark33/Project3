//change servo so that slow has a slower slope
//fast needs higher slope
//both use the same delay between periods
//intermittent uses low mode but delay between cycles changes

//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "windshield_wiper.h"
#include "servo.h"

//=====[Declaration of private defines]========================================

#define PERIOD 0.02
#define MIN_ANGLE 0.025
#define MAX_ANGLE 0.125
#define SLOPE (MAX_ANGLE - MIN_ANGLE)/(180-0)

//=====[Declaration of private data types]=====================================

PwmOut servo(PF_9);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float angleS = 0;

//=====[Declarations (prototypes) of private functions]========================

void servoMove(float angle);

//=====[Implementations of public functions]===================================

void servoInit() {
  servo.period(PERIOD);
  servoUpdate(SERVO_STOP);
}

void servoUpdate(servo_state_t state) {
  switch (state) {
  case SERVO_STOP:
    servoMove(0.0);
    break;
  case SERVO_LEFT:
    servoMove(0.0);
    break;
  case SERVO_RIGHT:
    servoMove(67.0);
    break;
  default:
    servoMove(0.0);
    break;
  }
}

//=====[Implementations of private functions]==================================

void servoMove(float angle) {
  servo.write(angle * SLOPE + MIN_ANGLE);
  angleS = angle;
}

