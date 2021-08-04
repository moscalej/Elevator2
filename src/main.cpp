


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

}



void loop()
{
    elevator.blink();
    while (globalState.errors){
        run_state_machine(&elevator, &globalState);
    }
//    run_resolve_error(&elevator, &globalState);

}