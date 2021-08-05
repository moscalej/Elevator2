//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_ARDUINO_H
#define UNTITLED4_ARDUINO_H

#include "config.h"
#include <Arduino.h>

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

    bool read_button(int button_number);

private:
    // Inputs
    int floor[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3};
    int button_call[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3};
    int door_censor[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3};
    int accelerator_censor = PIN0;

    //output
    int door_lock[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN4, PIN3, PIN3, PIN3, PIN3};
    int frequency_enable = PIN3;
    int frequency_on = PIN3;
    int frequency_direction = PIN3;
    int frequency_brake = PIN3;

    void move_up();
    void move_down();
    void move_break();
    void move_stop();

    int next_floor;

    bool read_floor(int floor_to_read);

    struct {
        int current_floor;
        int previous_floor;
        int next_floor;
        int final_floor;
        bool arrive_to_slow;
        bool leaving_slow;
        int slow_censor;
        int next_state;
    } state;
    int errors;

    void read_state();
};


#endif //UNTITLED4_ARDUINO_H
