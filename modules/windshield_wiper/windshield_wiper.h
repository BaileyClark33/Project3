//=====[#include guards - begin]===============================================

#ifndef _WINDSHIELD_H_
#define _WINDSHIELD_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
  WIPERS_OFF,
  WIPERS_INT,
  WIPERS_HI,
  WIPERS_LOW
} windshield_state_t;

windshield_state_t wiperState;

int delayState;
//=====[Declarations (prototypes) of public functions]=========================

void windshieldInit();
void windshieldUpdate();
void wipersReturn();

//=====[#include guards - end]=================================================

#endif // _WINDSHIELD_H_
