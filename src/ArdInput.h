//
// Created by amoscoso on 8/7/2021.
//

#ifndef ELEVATOR2_ARDINPUT_H
#define ELEVATOR2_ARDINPUT_H
#include <Arduino.h>

class ArdInput {
public:
    ArdInput(int pin_number, int memory);

    /**
     * This method will use a memory system where it need to have Memory times of the same input
     * to change the state, if not it will not change
     * @return 1 for high and 0 for low
     */
    int read_input();

    /**
     * This method will set the pin as a pull up input
     */
    void setup();

private:
    int counter;
    int pin_number;
    int state;
    int memory;
};


#endif //ELEVATOR2_ARDINPUT_H
