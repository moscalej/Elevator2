//
// Created by amoscoso on 8/7/2021.
//

#include "ArdInput.h"

ArdInput::ArdInput(int pin_number, int memory) {
    this->counter = memory;
    this->memory = memory;
    this->pin_number = pin_number;
    this->state = LOW;

}

void ArdInput::setup() {
    pinMode(this->pin_number, INPUT_PULLUP);
}

int ArdInput::read_input() {
    int dig_read = digitalRead(this->pin_number);
    if (this->state != dig_read) {
        if (this->counter == 0) {
            this->state = dig_read;
            this->counter = memory;
        } else {
            this->counter--;
        }

    } else {
        this->counter = this->memory;
    }
    return this->state;
}
