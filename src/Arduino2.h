//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_ARDUINO_H
#define UNTITLED4_ARDUINO_H

#include "config.h"
#include <Arduino.h>
#include "ArdInput.h"


#define MEMORY 5
typedef struct {
    int command = 0;
    int arguments = 0;
} Command;


class ArduinoInter {
public:

    /**
     * Set all the pins for the Arduino
     * @return
     */
    int setup();

    /**
     * This is use for debug
     * @return
     */
    int blink();

    /**
     * Check if the door is open on any floor
     * @return 1 if the do0r is open and 0 if close
     */
    int get_door_status();

    /**
     * Check if a button is press, if so it will return a command extructure
     * where if a button is press it will return move to that button, if not
     * it will return NO command
     * @return
     */
    Command check_buttons();

    /**
     * This will use the censor to move the elevator from one
     * floor to another, this will happen using a state machine and updating the states
     * until arriving to the destination.
     *
     * @param from_floor Witch floor the elevator is leaving.
     * @param to_floor Witch floor the elevator need to arrive.
     * @return
     */
    int move_to_floor(int from_floor, int to_floor);


    /**
     * Returns the errors that occurred during using the elevator
     * @return
     */
    int get_errors() const;

//    int bring_up();


private:
    // Inputs
//    int floor[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3, PIN3};
    ArdInput button_call[MAX_FLOOR] = {ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY)};

    ArdInput door_censor[MAX_FLOOR] = {ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                       ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY)};

    ArdInput accelerator_censor = ArdInput(PIN0, MEMORY);

    ArdInput floor[MAX_FLOOR] = {ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                 ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                 ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY),
                                 ArdInput(PIN0, MEMORY), ArdInput(PIN0, MEMORY)};

    //output
    int door_lock[MAX_FLOOR] = {PIN3, PIN3, PIN3, PIN4, PIN3, PIN3, PIN3, PIN3};
    int frequency_enable = PIN3;
    int frequency_on = PIN3;
    int frequency_direction = PIN3;
    int frequency_brake = PIN3;

    void move_general(int from_floor, int to_floor);
    void move_up() const;
    void move_down() const;
    void move_break() const;
    void move_stop() const;


    bool read_open_door_censor(int floor_to_read);

    /**
     * Will update the current floor
     * from the last read floor censor
     */
    int update_current_floor();

    struct {
        int current_floor;
        int previous_floor;
        int next_floor;
        int final_floor;
        bool is_door_open;
        int slow_censor;
        int next_state;
        int speed_state;
    } state;
    int errors;

    void update_elevator_state();
    int get_state_machine() const;
    void update_state_machine(int next_state);

    void unlock_door(int lock_number);
};


#endif //UNTITLED4_ARDUINO_H
