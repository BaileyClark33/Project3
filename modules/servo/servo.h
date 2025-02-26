//=====[#include guards - begin]===============================================

#ifndef _SERVO_H_
#define _SERVO_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
  SERVO_LEFT,
  SERVO_RIGHT,
  SERVO_STOP
} servo_state_t;

//=====[Declarations (prototypes) of public functions]=========================

void servoInit();
void servoUpdate(servo_state_t state);

//=====[#include guards - end]=================================================

#endif // _SERVO_H_
