//
// Created by amoscoso on 8/1/2021.
//

#include "StateMachine.h"

int run_state_machine(ElevatorClass *elevator, GlobalState *globalState) {
    int door;
    int command;

    switch (globalState->leer_stado()) {
        case BRING_UP:
            elevator->bring_up();
            globalState->proximo_stado(STAND_BY_CLOSE_DOOR);
            break;

        case RESET:
            elevator->reset();
            globalState->proximo_stado(BRING_UP);
            break;

        case STAND_BY_CLOSE_DOOR:
            door = elevator->get_door_status();
            command = elevator->get_command();
            if (door == OPEN) {
                globalState->proximo_stado(NO_HAGAS_NADA_PUERTA_ABIERTA);
            } else {
                if (command != NO_COMMAND) {
                    globalState->proximo_stado(EXECUTING_COMMAND);

                }
            }
            break;

        case NO_HAGAS_NADA_PUERTA_ABIERTA:
            command = elevator->get_command();
            if (elevator->get_door_status() == CLOSE) {
                globalState->proximo_stado(STAND_BY_CLOSE_DOOR);

            }
            break;

        case EXECUTING_COMMAND:
            elevator->run_command();
            globalState->proximo_stado(STAND_BY_CLOSE_DOOR);
            break;

    }

    if (elevator->get_erros() == NO_ERROR) {
        globalState->errors = elevator->get_erros();
        return -1;
    }
    return 0;
}