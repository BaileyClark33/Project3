//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "windshield_wiper.h"

//=====[Declaration of private defines]========================================

#define DUTY_LEFT_MAX 0.065 
#define DUTY_LEFT_SLOW 0.0725
#define DUTY_RIGHT_MAX 0.085
#define DUTY_RIGHT_SLOW 0.0775
#define DUTY_STOP 0.075
#define PERIOD 0.02 

//=====[Declaration of private data types]=====================================

typedef enum {
  SERVO_LEFT_F,
  SERVO_LEFT_S,
  SERVO_RIGHT_F,
  SERVO_RIGHT_S,
  SERVO_STOP
} servo_state_t;

PwmOut servo(PF_9); 


//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

servo_state_t servoState;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================


void servoInit() {
    servo.period(PERIOD); 
    servoState = SERVO_STOP;
    servoUpdate();
    servo.write(DUTY_STOP);
}

void servoUpdate() {
    switch(servoState) {
        case SERVO_STOP:
            servo.write(DUTY_MIN);
            break;
        case SERVO_LEFT:


    }
}

void setServoState(servo_state_t state) {
    servoState = state;
}
    // servo.write(DUTY_MIN);
    // delay(1000);
    // servo.write(DUTY_STOP);
    // delay(1000);
    // servo.write(DUTY_MAX);
    // delay(1000);