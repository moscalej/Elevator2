//
// Created by amoscoso on 8/4/2021.
//

#ifndef ELEVATOR2_CONFIG_H
#define ELEVATOR2_CONFIG_H

enum DoorStatus {
    OPEN = 1,
    CLOSE = 0,
};

enum CommandsNames {
    NO_COMMAND = 0,
    MOVE = 1,
    TURN_LIGHTS = 2,

};

enum States {
    BRING_UP = 0,
    RESET = 1,
    STAND_BY_CLOSE_DOOR = 2,
    NO_HAGAS_NADA_PUERTA_ABIERTA = 3,
    EXECUTING_COMMAND = 4,
    MOVING = 5,
};

enum Elevator{
    START_MOVE,
    MOVE_ELE,
    STOP_ELE,
    BREAK_ELE,
    OPEN_DOOR_ELE,
    FINISH_ELE,
};

enum ElevatorSpeed{
    LEAVING_SLOW,
    FAST,
    ENTERING_SLOW,
    ON_CENSOR,
};

enum ArdErrors{
    NO_ERROR,
    SKIP_CENSOR,
    WRONG_ELEVATOR_STATE,
    MULTIPLE_FLOOR_CENSOR_READ,
    UNKNOW_SPEED_STATE,
    MISS_BREAK_STATE,
};


#define MAX_FLOOR 8
#define DEBUG 0

#endif //ELEVATOR2_CONFIG_H
