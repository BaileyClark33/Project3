//=====[Libraries]=============================================================

#include "ignition.h"
#include "alarm.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "user_interface.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_BUTTON_TIME_MS        40

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

DigitalIn ignitionButton(BUTTON1);

DigitalIn driveSeatUsed(D10);
DigitalIn driveBelt(D11);
DigitalIn passSeatUsed(D12);
DigitalIn passBelt(D13);

DigitalOut engineLed(LED2);
DigitalOut ignitionLed(LED1);


static bool welcomed = false;

static int updateTime_ms = 10;

ignition_statement_t writeVal;

//=====[Declarations (prototypes) of private functions]========================

void welcomeMessage();
void failMessage();
void engineStartMessage();
void engineStopMessage();
void checkCanIgnite();
void engineStart();
void engineStop();
void ignitionFail();

//=====[Implementations of public functions]===================================

void ignitionInit() {
    driveSeatUsed.mode(PullDown);
    passSeatUsed.mode(PullDown);
    driveBelt.mode(PullDown);
    passBelt.mode(PullDown);
    ignitionButton.mode(PullDown);
}

void ignitionUpdate() {
    static int accumulatedDebounceTime = 0;
    if (!welcomed && driveSeatUsed == ON) {
        welcomeMessage();
        writeVal = INTRO;
        welcomed = true;
    }


    interfaceWrite("sigma", 5);
    checkCanIgnite();

    if (ignitionButton == ON) {
        accumulatedDebounceTime += updateTime_ms;
    }
    if (accumulatedDebounceTime >= DEBOUNCE_BUTTON_TIME_MS && ignitionButton == ON) {
        accumulatedDebounceTime = 0;
        if (alarmRead()) {
            alarmDisable();
        }
        else if (ignitionLed == ON) {
            engineStart();
        }
        else if (engineLed == ON) {
            engineStop();
        }
        else {
            ignitionFail();
        }
        }
        delay(updateTime_ms);
}

bool ignitionRead() {
    return engineLed == ON;
}

//=====[Implementations of private functions]==================================

void checkCanIgnite() {

    if (driveSeatUsed == ON && passSeatUsed == ON &&
        driveBelt == ON && passBelt == ON && engineLed == OFF) {
        ignitionLed = ON;
    } 
    else {
        ignitionLed = OFF;
    }
}

void engineStart() {
    engineLed = ON;
    ignitionLed = OFF;
    engineStartMessage();
    writeVal = START;
}

void engineStop() {
    engineLed = OFF;
    engineStopMessage();
    writeVal = STOP;
}

void ignitionFail() {
    alarmEnable();
    failMessage();
    writeVal = FAIL;
}

void welcomeMessage() {

    interfaceWrite("Welcome to enhanced alarm system model 218-W24\n", 47);
}

void engineStartMessage() {
    interfaceWrite("Engine Started\n", 16);
}

void engineStopMessage() {
    interfaceWrite("Engine Stopped\n", 16);
}

void failMessage() {
    interfaceWrite("Ignition inhibited\n", 20);

    if (driveSeatUsed == OFF) {
        interfaceWrite("Driver seat unoccupied\n", 24);
    }
    if (passSeatUsed == OFF) {
        interfaceWrite("Passenger seat unoccupied\n", 27);
    }
    if (driveBelt == OFF) {
        interfaceWrite("Driver seatbelt not fastened\n", 30);
    }
    if (passBelt == OFF) {
        interfaceWrite("Passenger seatbelt not fastened\n", 31);
    }
}

ignition_statement_t getIgnitionState() {
    return writeVal;
}

bool getDriveSeatUsed() { return driveSeatUsed == ON; }
bool getDriveBelt() { return driveBelt == ON; }
bool getPassSeatUsed() { return passSeatUsed == ON; }
bool getPassBelt() { return passBelt == ON; }
