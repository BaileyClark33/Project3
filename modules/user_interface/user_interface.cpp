//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "ignition.h"

#include "car_system.h"
#include "alarm.h"
#include "ignition.h"
#include "windshield_wiper.h"
#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
void statementSelect();
void easyWrite(const char * str, int x = 0, int y = 0);

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================

static void userInterfaceDisplayInit()
{
    displayInit();
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;
        statementSelect();

    } else {
        accumulatedDisplayTime += SYSTEM_TIME_INCREMENT_MS;        
    } 
}

void statementSelect() {
        easyWrite("Wiper:");
        switch (getWiperState()) {
            case WIPERS_HI:
                easyWrite("HI", 7);
                easyWrite("              ", 0, 1);
                break;
            case WIPERS_LOW:
                easyWrite("LOW", 7);
                easyWrite("              ", 0, 1);
                break;
            case WIPERS_INT:
                easyWrite("INT", 7);
                easyWrite("Delay:", 0, 1);
                switch(getDelayState()){
                    case 1000:
                    easyWrite("LONG", 7, 1);
                    break;
                case 500:
                    easyWrite("MEDIUM", 7, 1);
                    break;
                default:
                    easyWrite("SHORT", 7, 1);
                break;
                }
                break;
            default:
            case WIPERS_OFF:
                easyWrite("OFF", 7, 1);
                easyWrite("              ", 0, 1);
                break;
  }
}

void easyWrite(const char * str, int x, int y) {
    displayCharPositionWrite(x, y);
    displayStringWrite(str);
    // delay(delay);
}
