//=====[#include guards - begin]===============================================

#ifndef _WINDSHIELD_H_
#define _WINDSHIELD_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================



//=====[Declarations (prototypes) of public functions]=========================

void windshieldInit();
void windshieldUpdate();
windshield_state_t getWiperState();
int getDelayState();

//=====[#include guards - end]=================================================

#endif // _WINDSHIELD_H_
