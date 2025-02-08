//=====[Libraries]=============================================================

#include "mbed.h"
#include "alarm.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

DigitalInOut alarm(PE_10);

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool alarmEnabled = false;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void alarmInit() {
    alarm.mode(OpenDrain);
    alarm.input();
}

void alarmEnable() {
    alarm.output();
    alarmEnabled = true;
}

void alarmDisable() {
    alarm.input();
    alarmEnabled = false;
}

bool alarmRead() {
    return alarmEnabled;
}

//=====[Implementations of private functions]==================================