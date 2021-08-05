


#include <Arduino.h>
#include "ElevatorClass.h"
#include "StateMachine.h"
#define FIRMWARE_VERSION 10001
ElevatorClass  elevator; //EStado elevador
GlobalState  globalState; // Estado GlobaL
void setup()
{

    elevator.setup();
    globalState.proximo_stado(BRING_UP);
    globalState.firmware_version = FIRMWARE_VERSION;

}



void loop()
{
    elevator.blink();
//    Serial.print(globalState.errors);
    while (!globalState.errors){
//        Serial.print(0xb00b);
        run_state_machine(&elevator, &globalState);
    }
//    run_resolve_error(&elevator, &globalState);

}