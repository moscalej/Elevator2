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
    comando.command = NO_COMMAND;


    for (int button = 0; button < MAX_FLOOR; ++button) {
        if (this->button_call[button].read_input() == HIGH) {
            comando.command = MOVE;
            comando.arguments = button;
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

    this->update_state_machine(START_MOVE);
    bool moving = true;
    int distance_to_final;
    bool door_state;


    while (moving) {


        this->update_elevator_state();
        switch (this->get_state_machine()) {

            case START_MOVE:
                this->state.speed_state = ON_CENSOR;
                if (from_floor == to_floor) {
                    this->update_state_machine(STOP_ELE);
                }
                this->state.current_floor = from_floor;
                this->state.final_floor = to_floor;
                this->state.previous_floor = from_floor;
                this->state.is_door_open = false;
                this->update_state_machine(MOVE_ELE);

            case MOVE_ELE:

                distance_to_final = abs(this->state.current_floor - this->state.final_floor);
                switch (distance_to_final) {

                    case 0:

                        this->update_state_machine(STOP_ELE);
                        this->errors = MISS_BREAK_STATE;
                        break;

                    case 1:
                        if (this->state.speed_state == ENTERING_SLOW) {
                            this->update_state_machine(BREAK_ELE);
                        } else {
                            this->update_state_machine(MOVE_ELE);
                        }
                        break;


                    default:
                        this->state.next_state = MOVE_ELE;
                        break;
                }
                this->move_general(from_floor, to_floor);


            case BREAK_ELE:
                switch (this->state.speed_state) {
                    case ON_CENSOR:
                        this->update_state_machine(STOP_ELE);
                        break;
                    default:
                        //solo por seguridad
                        if (this->state.current_floor == to_floor) {
                            this->update_state_machine(STOP_ELE);
                        }
                        break;
                }

                this->move_break();
                break;
            case STOP_ELE:
                this->move_stop();
                this->update_state_machine(OPEN_DOOR_ELE);
                break;
            case OPEN_DOOR_ELE:
                door_state = this->get_door_status();
                this->unlock_door(this->state.current_floor);
                if (door_state == OPEN) {
                    this->update_state_machine(FINISH_ELE);
                }
            case FINISH_ELE:

                moving = false;
            default:
                this->errors = WRONG_ELEVATOR_STATE;

        }
    }

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
        if (this->door_censor[i].read_input() == HIGH) {
            return OPEN;
        }
    }
    return CLOSE;
}



int ArduinoInter::setup() {

    Serial.begin(9600);

    // Setting pins for the inputs
    for (int i = 0; i < MAX_FLOOR; ++i) {
        this->floor[i].setup();
        this->button_call[i].setup();
        this->door_censor[i].setup();
    }
    this->accelerator_censor.setup();

    // Setting output
    for (int i = 0; i < MAX_FLOOR; ++i) {
        pinMode(this->door_lock[i], OUTPUT);
    }
    pinMode(this->frequency_enable, OUTPUT);
    pinMode(this->frequency_on, OUTPUT);
    pinMode(this->frequency_direction, OUTPUT);
    pinMode(this->frequency_brake, OUTPUT);

    return 0;
}

void ArduinoInter::update_elevator_state() {

    this->state.current_floor = this->update_current_floor();
    this->state.slow_censor = this->accelerator_censor.read_input();
    this->state.is_door_open = this->get_door_status();

    int distance = abs(this->state.previous_floor - this->state.current_floor);

    switch (distance) {
        case 0:
            if (this->state.slow_censor == HIGH) {
                switch (this->state.speed_state) {
                    case ON_CENSOR:
                        this->state.speed_state = LEAVING_SLOW;
                        break;
                    case LEAVING_SLOW:
                        this->state.speed_state = LEAVING_SLOW;
                        break;
                    case FAST:
                        this->state.speed_state = ENTERING_SLOW;
                        break;
                    case ENTERING_SLOW:
                        this->state.speed_state = ENTERING_SLOW;
                        break;
                    default:
                        this->errors = UNKNOW_SPEED_STATE;

                }
            } else {
                this->state.speed_state = FAST;
            }

            break;
        case 1:
            // llegal al piso
            this->state.previous_floor = this->state.current_floor;
            this->state.speed_state = ON_CENSOR;
        default:
            // ACA hay uno problema de faltar un error pero igual el programa fuinciona
            this->state.previous_floor = this->state.current_floor;
            this->state.speed_state = ON_CENSOR;
            this->errors = SKIP_CENSOR;
    }

}

int ArduinoInter::update_current_floor() {

    int counter = 0;
    int current_floor;
    for (int floor_number = 0; floor_number < MAX_FLOOR; ++floor_number) {
        if (this->floor[floor_number].read_input() == HIGH) {
            this->state.current_floor = floor_number;
            current_floor = floor_number;
            counter++;
        }
    }
    if (counter > 1) {
        this->errors = MULTIPLE_FLOOR_CENSOR_READ;
    }
    return current_floor;
}


void ArduinoInter::move_general(int from_floor, int to_floor) {
    if (from_floor == to_floor) {
        this->move_break();
    } else if (from_floor < to_floor) {
        move_up();
    } else {
        move_down();
    }

}

void ArduinoInter::update_state_machine(int next_state) {
    this->state.next_state = next_state;

}

void ArduinoInter::unlock_door(int lock_number) {
    digitalWrite(this->door_lock[lock_number], HIGH);
}

int ArduinoInter::get_state_machine() const {
    return this->state.next_state;
}

void ArduinoInter::move_up() const {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, HIGH);
    digitalWrite(this->frequency_direction, LOW);
    digitalWrite(this->frequency_brake, HIGH);
}


void ArduinoInter::move_down() const {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, HIGH);
    digitalWrite(this->frequency_direction, HIGH);
    digitalWrite(this->frequency_brake, HIGH);
}

void ArduinoInter::move_break() const {
    digitalWrite(this->frequency_enable, HIGH);
    digitalWrite(this->frequency_on, LOW);
    digitalWrite(this->frequency_brake, HIGH);
}

void ArduinoInter::move_stop() const {
    digitalWrite(this->frequency_enable, LOW);
    digitalWrite(this->frequency_on, LOW);
    digitalWrite(this->frequency_direction, LOW);
    digitalWrite(this->frequency_brake, LOW);
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

int ArduinoInter::get_errors() const {
    return this->errors;
}
