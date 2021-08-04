//
// Created by amoscoso on 8/1/2021.
//

#include "Arduino2.h"
#include <Arduino.h>

/**
 * Tiene que revisar que comandoes voy a correr
 * @return
 */
Command ArduinoInter::check_buttons() {
    Command comando;
    comando.command = 0;

    return comando;
}

/**
 * Le digo al ardunio que no me importa como lo hagas
 * llevame del piso que te digo al piso que te digo
 * @param from_floor
 * @param to_floor
 * @return
 */
int ArduinoInter::move_to_floor(int from_floor, int to_floor) {


    return 0;
}

/**
 * Aca es cuando usas el arduino para ver si alguna puerta esta
 * abierta o cerrada.
 * @return 1 si la puerta esta abierta
 *          0 si la puerta esta cerrada
 */
int ArduinoInter::get_door_status() {
    return 0;
}

int ArduinoInter::get_errors() {
    return 0;
}

int ArduinoInter::bring_up() {
    return 0;
}

int ArduinoInter::setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN3, INPUT_PULLUP);
    return 0;
}

int ArduinoInter::blink() {
    digitalWrite(LED_BUILTIN, HIGH);

    // wait for a second
    delay(2000);

    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);

    // wait for a second
    delay(2000);
    return 0;
}
