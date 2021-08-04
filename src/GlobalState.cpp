//
// Created by amoscoso on 8/1/2021.
//

#include "GlobalState.h"
#include <Arduino.h>

int GlobalState::proximo_stado(int state) {
    this->current_state = state;
    return 0;

}

int GlobalState::leer_stado() const {
    if (Serial.available()){
        Serial.print(this->current_state );
    }
    return this->current_state;
}