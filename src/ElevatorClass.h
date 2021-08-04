//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_ELEVATORCLASS_H
#define UNTITLED4_ELEVATORCLASS_H

#include "Arduino2.h"

enum DoorStatus {
    OPEN = 1,
    CLOSE = 0,
};

enum CommandsNames {
    NO_COMMAND = 0,
    MOVE = 1,
    TURN_LIGHTS = 2,

};




class ElevatorClass {

public:
    int current_floor = 0;
    bool running = false;

    int destination_floor = 0;
    bool is_door_open = true;


    int update_elevator_state(int elevatorState);

    // Se tienen que definir
    int bring_up();

    void reset();


    int get_door_status();

    int get_command();

    void run_command();

    int get_erros();
    int setup();

    int blink();

private:
    ArduinoInter arduino;
    int errors;
    bool commando_en_espera;
    Command command_to_run;
};

enum Errors {
    NO_ERROR,

};


#endif //UNTITLED4_ELEVATORCLASS_H
