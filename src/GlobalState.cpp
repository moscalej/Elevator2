//
// Created by amoscoso on 8/1/2021.
//

#include "GlobalState.h"

int GlobalState::proximo_stado(int state) {
    this->current_state = state;
    return 0;

}

int GlobalState::leer_stado() const {
    return this->current_state;
}