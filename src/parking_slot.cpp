#include "parking_lot.h"

parking_slot::parking_slot() {
    this->set_state(true);
    this->set_floor_number(0);
    this->set_slot_number(0);
    this->parked_vehicle = new vehicle();
    // this->parked_vehicle = nullptr;
}

parking_slot::parking_slot(int floor_number, int slot_number) {
    this->set_state(true);
    this->set_floor_number(floor_number);
    this->set_slot_number(slot_number);
    this->parked_vehicle = new vehicle();
    // this->parked_vehicle = nullptr;
}

parking_slot::~parking_slot() {
    delete this->parked_vehicle;
}

bool parking_slot::get_state() {
    return this->is_empty;
}

void parking_slot::set_state(bool state) {
    this->is_empty = state;
}

int parking_slot::get_floor_number() {
    return this->floor_number;
}

void parking_slot::set_floor_number(int floor_number) {
    this->floor_number = floor_number;
}

int parking_slot::get_slot_number() {
    return this->slot_number;
}

void parking_slot::set_slot_number(int slot_number) {
    this->slot_number = slot_number;
}

void parking_slot::park_vehicle(vehicle* vehicle) {
    if(this->get_state() == false){
        std::cerr << "The slot is not empty" << std::endl;
        return;
    } else {
        this->set_state(false);
        *(this->parked_vehicle) = *(vehicle);
    }
}

void parking_slot::remove_vehicle() {
    this->set_state(true);
}

