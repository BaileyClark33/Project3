//=====[#include guards - begin]===============================================

#ifndef _SERVO_H_
#define _SERVO_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
  SERVO_LEFT_F,
  SERVO_LEFT_S,
  SERVO_RIGHT_F,
  SERVO_RIGHT_S,
  SERVO_STOP
} servo_state_t;

//=====[Declarations (prototypes) of public functions]=========================

void servoInit();
void servoUpdate();
void getServoState(servo_state_t);

//=====[#include guards - end]=================================================

#endif // _SERVO_H_
