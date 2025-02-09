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

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
void statementSelect(ignition_statement_t cmd);

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
     
    // displayCharPositionWrite ( 0,0 );
    // displayStringWrite( "Tmp:" );

    // displayCharPositionWrite ( 9,0 );
    // displayStringWrite( "Gas:" );
    
    // displayCharPositionWrite ( 0,1 );
    // displayStringWrite( "Alarm:" );
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    // char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;
        statementSelect(writeVal);
        // sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
        // displayCharPositionWrite ( 4,0 );
        // displayStringWrite( temperatureString );
        // displayCharPositionWrite ( 6,0);
        // displayStringWrite( "'C" );

        // displayCharPositionWrite ( 13,0 );

        // if ( gasDetectorStateRead() ) {
        //     displayStringWrite( "D    " );
        // } else {
        //     displayStringWrite( "ND" );
        // }

        // displayCharPositionWrite ( 6,1 );
        
        // if ( sirenStateRead() ) {
        //     displayStringWrite( "ON " );
        // } else {
        //     displayStringWrite( "OFF" );
        // }

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

void statementSelect(ignition_statement_t cmd) {
    switch(cmd) {
        case INTRO:
            displayInit();
            displayCharPositionWrite ( 0,0 );
            displayStringWrite("Welcome to enhanced alarm system model 218-W24");
            delay(1000);
            break;
        case FAIL:
            displayInit();
            displayCharPositionWrite ( 0,0 );
            displayStringWrite("Ignition inhibited");
            delay(1000);
            break;
        case START:
            displayInit();
            displayCharPositionWrite ( 0,0 );
            displayStringWrite("Engine Started");
            delay(1000);
            break;
        case STOP:
            displayInit();
            displayCharPositionWrite ( 0,0 );
            displayStringWrite("Engine Stopped");
            delay(1000);
            break;
        default:
        break;
    }
}