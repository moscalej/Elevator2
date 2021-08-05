//
// Created by amoscoso on 8/1/2021.
//

#ifndef UNTITLED4_GLOBALSTATE_H
#define UNTITLED4_GLOBALSTATE_H

#include "config.h"



class GlobalState {
public:
    int firmware_version = 0;
    int current_state = BRING_UP;
    int last_state = RESET;
    bool fatalError = false;
    int errors;

    int proximo_stado(int states);

    int leer_stado() const;
};

#endif //UNTITLED4_GLOBALSTATE_H
