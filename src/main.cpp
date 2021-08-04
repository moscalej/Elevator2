


#include "ElevatorClass.h"
#include "StateMachine.h"
#include <Arduino.h>
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

}