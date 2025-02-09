//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    INTRO,
    FAIL,
    START,
    STOP
} ignition_statement_t;

ignition_statement_t writeVal;

//=====[Declarations (prototypes) of public functions]=========================

void ignitionInit();
void ignitionUpdate();
bool ignitionRead();

//=====[#include guards - end]=================================================

#endif // _IGNITION_H_