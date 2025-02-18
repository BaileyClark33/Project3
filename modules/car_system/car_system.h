//=====[#include guards - begin]===============================================

#ifndef _CAR_SYSTEM_H_
#define _CAR_SYSTEM_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

#define SYSTEM_TIME_INCREMENT_MS   1

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void carSystemInit();
void carSystemUpdate();

//=====[#include guards - end]=================================================

#endif // _CAR_SYSTEM_H_