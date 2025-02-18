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

//=====[Declarations (prototypes) of private functions]========================

void servoMove(float angle, float delay);

//=====[Implementations of public functions]===================================

void servoInit() {
  servo.period(PERIOD);
  servoReturn();
}

void servoUpdate(servo_state_t state) {
  switch (state) {
  case SERVO_STOP:
    servoMove(servo.read(), 0.01);
    break;
  case SERVO_LEFT_S:
    servoMove(0.0, 0.1);
    break;
  case SERVO_LEFT_F:
    servoMove(0.0, 0.01);
    break;
  case SERVO_RIGHT_S:
    servoMove(180.0, 0.1);
    break;
  case SERVO_RIGHT_F:
    servoMove(180.0, 0.01);
    break;
  default:
    servoMove(servo.read(), 0.01);
    break;
  }
}

// void setServoState(servo_state_t state) { servoState = state; }

//=====[Implementations of private functions]==================================

void servoMove(float angle, float delay) {
  servo.write(angle * SLOPE + MIN_ANGLE);
  delay(delay);
}

void servoReturn() {
    if (servo.read() < 2) {
    servoUpdate(SERVO_STOP);
    } else {
        servoUpdate(SERVO_RIGHT_F);
    }
}

float getServoAngle() {
    return servo.read();
}
