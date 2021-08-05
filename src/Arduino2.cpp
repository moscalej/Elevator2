//
// Created by amoscoso on 8/1/2021.
//

#include "Arduino2.h"

/**
 * Tiene que revisar que comandoes voy a correr
 * @return
 */


Command ArduinoInter::check_buttons() {
    Command comando;
    comando.command = 0;


    if (DEBUG){
        if (Serial.available()){
            comando.command = Serial.parseInt();
            comando.arguments = Serial.parseInt();

        }
        this->blink();
    }else{
        for (int button = 0; button < MAX_FLOOR; ++button) {
            if (this->read_button(button)){
                comando.command = MOVE;
                comando.arguments = button;
            }
            
        }
    }

    return comando;
}

/**
 * Le digo al ardunio que no me importa como lo hagas
 * llevame del piso que te digo al piso que te digo
 *
 * First will calculate the trajectory, then move and then
 * eneble the lock
 *
 * @param from_floor
 * @param to_floor
 * @return
 */
int ArduinoInter::move_to_floor(int from_floor, int to_floor) {


    if (to_floor == from_floor){

    }else if (to_floor > from_floor){
        int count = to_floor - from_floor;
        this->move_up();
        while (!digitalRead(this->accelerator_censor)){
            this->move_break();
            if (this->read_floor(this->next_floor)){

            }
        }

    }else{

    }
    bool direction = (from_floor>)
    this=mov


    return 0;
}

/**
 * Aca es cuando usas el arduino para ver si alguna puerta esta
 * abierta o cerrada.
 * @return 1 si la puerta esta abierta
 *          0 si la puerta esta cerrada
 */
int ArduinoInter::get_door_status() {
    for (int i = 0; i < MAX_FLOOR; ++i) {
        if (digitalRead(this->door_censor[i])){
            return OPEN;
        }
    }
    return CLOSE;
}

int ArduinoInter::get_errors() {
    return 0;
}

int ArduinoInter::bring_up() {
    return 0;
}

int ArduinoInter::setup() {

    Serial.begin(9600);

    // Setting pins for the inputs
    for (int i  = 0; i < MAX_FLOOR ; ++i) {
        pinMode(this->floor[i], INPUT_PULLUP);
        pinMode(this->button_call[i], INPUT_PULLUP);
        pinMode(this->door_censor[i], INPUT_PULLUP);
    }
    pinMode(this->accelerator_censor, INPUT_PULLUP);

    // Setting output
    for (int i  = 0; i < MAX_FLOOR ; ++i) {
        pinMode(this->door_lock[i], OUTPUT);
    }
    pinMode(this->frequency_enable, OUTPUT);
    pinMode(this->frequency_on, OUTPUT);
    pinMode(this->frequency_direction, OUTPUT);
    pinMode(this->frequency_brake, OUTPUT);

    return 0;
}

int ArduinoInter::blink() {
    digitalWrite(LED_BUILTIN, HIGH);

    // wait for a second
    delay(500);

    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);

    // wait for a second
    delay(500);
    return 0;
}

bool ArduinoInter::read_button(int button_number) {
    if (digitalRead(button_number)){
        delay(1);
        if (digitalRead(button_number)){
            return true;
        }
    }
    return false;
}

void ArduinoInter::move_up() {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, HIGH);
    digitalWrite(this->frequency_direction, LOW);
    digitalWrite(this->frequency_brake, LOW);

}

void ArduinoInter::move_down() {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, HIGH);
    digitalWrite(this->frequency_direction, HIGH);
    digitalWrite(this->frequency_brake, LOW);


}

void ArduinoInter::move_break() {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, LOW);
    digitalWrite(this->frequency_brake, LOW);

}

void ArduinoInter::move_stop() {
    digitalWrite(this->frequency_enable, LOW); // NEED to check this
    digitalWrite(this->frequency_on, LOW);
    digitalWrite(this->frequency_brake, HIGH);

}

bool ArduinoInter::read_floor(int floor_to_read) {

    if (digitalRead(this->door_censor[floor_to_read])){
        return true;
    }
    return false;
}

void ArduinoInter::read_state(){
    for (int i = 0; i < MAX_FLOOR; ++i) {
        if (digitalRead(this->floor[i])){
            this->state.current_floor = i;
            }
        }
    this->state.slow_censor = digitalRead(this->accelerator_censor);
    int distance = abs(this->state.previous_floor - this->state.current_floor);

    switch (distance) {
        case 0:
            this->state.leaving_slow = true;
            break;
        case 1:

            this->state.previous_floor = this->state.current_floor;
            if (this->state.slow_censor){
                this->state.leaving_slow = false;

            }
            default:
                this->errors = SKIP_CENSOR;
    }

        int distance_to_final = abs(this->state.current_floor - this->state.final_floor);
    switch (distance_to_final) {
        case 0:
            this->state.next_state = STOP_ELE;
            break;
        case 1:
            if (this->state.slow_censor == true and this->state.leaving_slow == false){

                this->state.next_state = BREAK_ELE;
            }
            this->state.next_state = MOVE_ELE;
            break;

        default:
            this->state.next_state = MOVE_ELE;

    }



    this->state.slow_censor = digitalRead(this->accelerator_censor);


}