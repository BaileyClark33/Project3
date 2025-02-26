//=====[#include guards - begin]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void displayInit();
 
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

void displayStringWrite( const char * str );

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_