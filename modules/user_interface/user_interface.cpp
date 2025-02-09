//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "car_system.h"
#include "alarm.h"
#include "daylight_sensor.h"
#include "headlights.h"
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

DigitalIn driveSeatUsed(D0);
DigitalIn driveBelt(D1);
DigitalIn passSeatUsed(D2);
DigitalIn passBelt(D3);

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
void statementSelect(ignition_statement_t cmd);
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
        statementSelect(writeVal);

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

void statementSelect(ignition_statement_t cmd) {
    easyWrite("                   ", 0, 0);
    easyWrite("                   ", 1, 0);
    switch(cmd) {
        case INTRO:
            easyWrite("Welcome to enhanced alarm");
            easyWrite("system model 218-W24", 0, 1);
            break;
        case FAIL:
            easyWrite("Ignition inhibited");
            easyWrite("Errors", 0, 1);
            if (driveSeatUsed == OFF) {
                easyWrite("DS", 7, 1);
            }
            if (passSeatUsed == OFF) {
                easyWrite("PS", 10, 1);
            }
            if (driveBelt == OFF) {
                easyWrite("DSB", 13, 1);
            }
            if (passBelt == OFF) {
                easyWrite("PSB", 16, 1);
            }
            break;
        case START:
            easyWrite("Engine Started");
            easyWrite("Wiper:", 0, 1);
            switch (wiperState) {
                case WIPERS_HI:
                    easyWrite("HI", 7, 1);
                    break;
                case WIPERS_LOW:
                    easyWrite("LOW", 7, 1);
                    break;
                case WIPERS_INT:
                    easyWrite("INT", 7, 1);
                    easyWrite("Delay:", 11, 1);
                    if (delayState == 1000) {
                        easyWrite("L", 18, 1);
                    }
                    else if (delayState == 500) {
                        easyWrite("M", 18, 1);
                    }
                    else {
                        easyWrite("S", 18, 1);
                    }
                    break;
                default:
                case WIPERS_OFF:
                    easyWrite("OFF", 7, 1);
                    break;
  }
        case STOP:
            easyWrite("Engine Stopped");
            break;
        default:
        break;
    }
}

void easyWrite(const char * str, int x, int y) {
    displayCharPositionWrite (x, y);
    displayStringWrite(str);
    // delay(delay);
}