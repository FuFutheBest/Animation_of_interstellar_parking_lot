#include "parking_lot.h"

parking_lot::parking_lot(int floors, int* slots) {
    this->set_floor_number(floors);
    int all_slots = 0;
    for (int i = 0; i < floors; i++) {
        all_slots += slots[i];
    }
    this->set_all_slots(all_slots);
    this->slots = slots;
    this->parking_slots = new parking_slot[all_slots];
}

parking_lot::parking_lot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int floors = dis(gen);
    this->slots = new int[floors];
    std::uniform_int_distribution<> dis2(1, 20);
    for (int i = 0; i < floors; i++) {
        this->slots[i] = dis2(gen);
    }
    this->set_floor_number(floors);
    int all_slots = 0;
    for (int i = 0; i < floors; i++) {
        all_slots += this->slots[i];
    }
    this->set_all_slots(all_slots);
    this->parking_slots = new parking_slot[all_slots];
    int index = 0;
    for(int i = 0; i < floors; i++){
        for(int j = 0; j < this->slots[i]; j++){
            this->parking_slots[index].set_floor_number(i);
            this->parking_slots[index].set_slot_number(j);
            index++;
        }
    }
}

parking_lot::~parking_lot() {
    delete[] this->parking_slots;
    delete[] this->slots;
}

int parking_lot::get_floor_number() {
    return this->floors;
}

void parking_lot::set_floor_number(int floor_number) {
    this->floors = floor_number;
}

int parking_lot::get_slot_number(int floor) {
    return this->slots[floor];
}

void parking_lot::set_slot_number(int slot_number, int floor) {
    this->slots[floor] = slot_number;
}

int parking_lot::get_all_slots() {
    return this->all_slots;
}

void parking_lot::set_all_slots(int all_slots) {
    this->all_slots = all_slots;
}

parking_slot* parking_lot::get_parking_slots() {
    return this->parking_slots;
}

int parking_lot::cal_empty_slot() {
    int res = 0;
    for (int i = 0; i < this->get_all_slots(); i++) {
        if (this->parking_slots[i].get_state()) {
            res ++;
        }
    }
    return res;
}

int parking_lot::cal_empty_slot(int floor) {
    int res = 0;
    int before = 0;
    for(int i = 0; i < floor; i++){
        before += this->get_slot_number(i);
    }
    for (int i = 0; i < this->get_slot_number(floor); i++) {
        if(this->parking_slots[before + i].get_state()){
            res ++;
        }
    }
    return res;
}

void parking_lot::print_parking_lot() {
    std::cout << "Welcome !\n";
    std::cout << "This parking lot has " << this->get_floor_number() << " floors and " << this->get_all_slots() << " slots.\n";
    std::cout << "There are " << this->cal_empty_slot() << " empty slots.\n";
    for (int i = 0; i < this->get_floor_number(); i++) {
        std::cout << "Floor " << i << ", " << this->get_slot_number(i) << " slots and " << this->cal_empty_slot(i) << " empty slots.\n";
    }
}

parking_slot* parking_lot::find_empty_slot(){
    for(int i = 0; i < this->get_all_slots(); i++){
        if(this->parking_slots[i].get_state()){
            return this->parking_slots + i;
        }
    }
    return nullptr;
}

void parking_lot::hint(vehicle in){
    this->print_parking_lot();
    std::cout << '\n';

    parking_slot* empty_slot = this->find_empty_slot();
    if(empty_slot == nullptr){
        std::cerr << "No empty slot.\n";
        exit(1);
    } else {
        std::cout << "Your arrival time is 0.00\n"; // change latter
        std::cout << "Your vehicle type is "; 
        in.print_vehicle();
        std::cout << '\n';
        std::cout << "The closest empty slot is on floor " << empty_slot->get_floor_number() << " and slot number is " << empty_slot->get_slot_number() << '\n';
    }
}

void parking_lot::ticket() {
    std::cout << "Your arrival time is 0.00\n"; // change latter
    std::cout << "Your vehicle type is 0\n"; // change latter
    std::cout << "You spend 0.00 in our parking lot.\n"; // change latter
    std::cout << "You need to pay 0.00 $.\n";
    std::cout << "Thank you for using our parking lot.\n";
}

void parking_lot::park_vehicle(vehicle* vehicle) {
    if(this->cal_empty_slot() == 0){
        std::cerr << "No empty slot.\n";
        exit(1);
    } else {
        this->find_empty_slot()->park_vehicle(vehicle);
    }
}

void parking_lot::park_vehicle(vehicle* vehicle, int floor, int slot) {
    int before = 0;
    for(int i = 0; i < floor; i++){
        before += this->get_slot_number(i);
    }
    this->parking_slots[before + slot].park_vehicle(vehicle);
}

void parking_lot::remove_vehicle(int floor, int slot) {
    int before = 0;
    for(int i = 0; i < floor; i++){
        before += this->get_slot_number(i);
    }
    this->parking_slots[before + slot ].remove_vehicle();
}