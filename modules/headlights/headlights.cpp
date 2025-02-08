//=====[Libraries]=============================================================

#include "mbed.h"
#include "headlights.h"
#include "arm_book_lib.h"
#include "daylight_sensor.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
    LIGHTS_OFF,
    LIGHTS_AUTO,
    LIGHTS_ON
} selector_state_t_;

typedef enum {
    HIBEAM,
    OFFBEAM
 } lamp_level_t_;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

AnalogIn headlightSelect(A0);
DigitalOut leftLamp(D12);
DigitalOut rightLamp(D13);
DigitalOut lefthiBeam(D6);
DigitalOut righthiBeam(D7);

DigitalIn hibeamSwitch(D5);

selector_state_t_ lightSelect;
lamp_level_t_ beamSelect;

//=====[Declarations (prototypes) of private functions]========================

void headlightsOff();
void headlightsOn();
void headlightsAuto();
void selectorUpdate();
void hibeamsOff();
void hibeamsOn();

//=====[Implementations of public functions]===================================

void headlightsUpdate() {
    selectorUpdate();
    daylightSensorUpdate();
    if (!ignitionRead()) {
        lightSelect = LIGHTS_OFF;
    }
    switch(lightSelect) {
        case LIGHTS_OFF:
            headlightsOff();
            hibeamsOff();
            break;
        case LIGHTS_AUTO:
            headlightsAuto();
            break;
        case LIGHTS_ON:
            headlightsOn();
            break;
        default:
            lightSelect = LIGHTS_OFF;
    }
}

void headlightsInit() {
    lightSelect = LIGHTS_OFF;
    beamSelect = OFFBEAM;
    daylightSensorInit();
    hibeamSwitch.mode(PullDown);
}

//=====[Implementations of private functions]==================================

void headlightsOff() {
    rightLamp = OFF; 
    leftLamp = OFF; 
    hibeamsOff();
}

void hibeamsOff() {
    lefthiBeam = OFF; 
    righthiBeam = OFF; 
}

void headlightsAuto() {
    bool daylight = readLightSensor();
    if (daylight) { 
        headlightsOff();
    } 
    else {
        headlightsOn();
    }
}

void headlightsOn() {
    if (ignitionRead()) {
        rightLamp = ON;
        leftLamp = ON;
    }
    if (hibeamSwitch == ON) {
        hibeamsOn();
    } else {
        hibeamsOff();
    }
}

void hibeamsOn() {
    if (ignitionRead()) {
        lefthiBeam = ON; 
        righthiBeam = ON;
    }
}

void selectorUpdate() {
    float selectorVal = headlightSelect.read();
    if (selectorVal >= 0.8) {
        lightSelect = LIGHTS_ON;
    } 
    else if (0.2 < selectorVal && selectorVal < 0.8) {
        lightSelect = LIGHTS_AUTO;
    }
    else {
        lightSelect = LIGHTS_OFF;
  }
}
