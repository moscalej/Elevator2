//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_ARDUINO_H
#define UNTITLED4_ARDUINO_H

typedef struct {
    int command = 0;
    int arguments = 0;
} Command;


class ArduinoInter {
public:
    int setup();
    int blink();
    int get_door_status();

    Command check_buttons();

    int move_to_floor(int from_floor, int to_floor);

    int get_errors();

    int bring_up();
};


#endif //UNTITLED4_ARDUINO_H
