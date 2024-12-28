#include <iostream>
#include <random>
#include "vehicle.h"
#define money_per_hour 10


float vehicle::get_price(float arrival_time, float time_now) {
    return (time_now - arrival_time) * money_per_hour;
}

void vehicle::print_vehicle() {
    switch (this->type) {
        case 0:
            std::cout << "Van";
            break;
        case 1:
            std::cout << "Car";
            break;
        case 2:
            std::cout << "Motorcycle";
            break;
        case 3:
            std::cout << "Bicycle";
            break;
        default:
            std::cerr << "Invalid type";
            exit(1);
    }
}

int vehicle::get_type() {
    return this->type;
}

void vehicle::set_type(int type) {
    this->type = type;
}

float vehicle::get_arrival_time() {
    return this->arrival_time;
}

void vehicle::set_arrival_time(float arrival_time) {
    this->arrival_time = arrival_time;
}

van::van() {
    this->set_type(0);
}

van::van(float arrival_time) {
    this->set_type(0);
    this->set_arrival_time(arrival_time);
}

car::car() {
    this->set_type(1);
}

car::car(float arrival_time) {
    this->set_type(1);
    this->set_arrival_time(arrival_time);
}

motorcycle::motorcycle() {
    this->set_type(2);
}

motorcycle::motorcycle(float arrival_time) {
    this->set_type(2);
    this->set_arrival_time(arrival_time);
}

bicycle::bicycle() {
    this->set_type(3);
}

bicycle::bicycle(float arrival_time) {
    this->set_type(3);
    this->set_arrival_time(arrival_time);
}

vehicle generate_vehicle(float arrival_time) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int type = dis(gen);
    vehicle res;
    switch (type) {
        case 0:
            res = van(arrival_time);
            break;
        case 1:
            res = car(arrival_time);
            break;
        case 2:
            res = motorcycle(arrival_time);
            break;
        case 3:
            res = bicycle(arrival_time);
            break;
        default:
            std::cerr << "Invalid type";
            exit(1);
    }
    std::cout << "at " << arrival_time << " comes a ";
    res.print_vehicle();
    std::cout << '\n';
    return res;
}
