//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_ELEVATORCLASS_H
#define UNTITLED4_ELEVATORCLASS_H

#include "Arduino2.h"


class ElevatorClass {

public:
    int current_floor = 0;

//    int destination_floor = 0;
    bool is_door_open = true;


    // Se tienen que definir
    static int bring_up();

    void reset();

    int get_door_status();

    int get_command();

    void run_command();

    int get_errors() const;

    int setup();

    static int blink();

private:
    ArduinoInter arduino;
    int errors{0};
    bool commando_en_espera = false;
    Command command_to_run;
};


#endif //UNTITLED4_ELEVATORCLASS_H
