//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_STATEMACHINE_H
#define UNTITLED4_STATEMACHINE_H

#include "ElevatorClass.h"
#include "GlobalState.h"
int run_state_machine(ElevatorClass * elevator, GlobalState * globalState);

int run_resolve_error(ElevatorClass * elevatorStates,  GlobalState * globalState);



#endif //UNTITLED4_STATEMACHINE_H
