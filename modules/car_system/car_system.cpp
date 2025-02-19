//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "car_system.h"
#include "ignition.h"
#include "windshield_wiper.h"
#include "display.h"
#include "user_interface.h"
#include "servo.h"
#include "alarm.h"
#include "serial_monitor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void carSystemInit()
{
    userInterfaceInit();
    ignitionInit();
    windshieldInit();
    alarmInit();
}

void carSystemUpdate()
{
    ignitionUpdate();
    windshieldUpdate();
    userInterfaceUpdate();
    serialMonitorUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
