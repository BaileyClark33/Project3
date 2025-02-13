//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "windshield_wiper.h"
#include "servo.h"

//=====[Declaration of private defines]========================================

#define DUTY_LEFT_MAX 0.065
#define DUTY_LEFT_SLOW 0.0725
#define DUTY_RIGHT_MAX 0.085
#define DUTY_RIGHT_SLOW 0.0775
#define DUTY_STOP 0.075
#define PERIOD 0.02
#define MIN_ANGLE 0.025
#define MAX_ANGLE 0.125
#define SLOPE 0.00055555555555

//=====[Declaration of private data types]=====================================

PwmOut servo(PF_9);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void servoInit() {
  servo.period(PERIOD);
  servoUpdate(SERVO_RIGHT_F);
  delay(200);
  servoUpdate(SERVO_STOP);
}

void servoUpdate(servo_state_t state) {
  switch (state) {
  case SERVO_STOP:
    servoMove(servo.read(), 0.01);
    break;
  case SERVO_LEFT_S:
    servoMove(0, 0.1);
    break;
  case SERVO_LEFT_F:
    servoMove(0, 0.01);
    break;
  case SERVO_RIGHT_S:
    servoMove(180, 0.1);
    break;
  case SERVO_RIGHT_F:
    servoMove(180, 0.01);
    break;
  default:
    servoMove(servo.read(), 0.01);
    break;
  }
}

// void setServoState(servo_state_t state) { servoState = state; }

//=====[Implementations of private functions]==================================

servoMove(int angle, int delay) {
  servo.write(angle * SLOPE + MIN_ANGLE);
  delay(delay);
}


// servo.write(DUTY_MIN);
// delay(1000);
// servo.write(DUTY_STOP);
// delay(1000);
// servo.write(DUTY_MAX);
// delay(1000);
