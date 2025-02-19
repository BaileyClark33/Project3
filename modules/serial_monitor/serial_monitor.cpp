//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition.h"
#include "serial_monitor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

void uartCommands(ignition_statement_t cmd);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Implementations of public functions]===================================

void serialMonitorUpdate() {
    statementSelect(getIgnitionState());
}

//=====[Implementations of private functions]==================================

void statementSelect(ignition_statement_t cmd) {
    switch(cmd) {
        case INTRO:
            uartUsb.write("Welcome to enhanced alarm system model 218-W24\n", 47);
            break;
        case FAIL:
            uartUsb.write("Ignition inhibited\n", 20);
            if (getDriveSeatUsed() == OFF) {
                uartUsb.write("Driver seat unoccupied\n", 24);
            }
            if (getPassSeatUsed() == OFF) {
                uartUsb.write("Passenger seat unoccupied\n", 27);
            }
            if (getDriveBelt() == OFF) {
                uartUsb.write("Driver seatbelt not fastened\n", 30);
            }
            if (getPassBelt() == OFF) {
                uartUsb.write("Passenger seatbelt not fastened\n", 311);
            }
            break;
        case START:
            uartUsb.write("Engine Started\n", 16);
        case STOP:
        uartUsb.write("Engine Stopped\n", 16);
    }
}
void uartCommands(ignition_statement_t cmd);