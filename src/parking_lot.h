#ifndef PARKING_LOT_H
#define PARKING_LOT_H
#include <iostream> 
#include "vehicle.h"
#include <random>

class parking_slot {
    public:
        parking_slot();
        parking_slot( int floor_number, int slot_number);
        ~parking_slot();
        bool get_state();
        void set_state( bool state );
        int get_floor_number();
        void set_floor_number(int floor_number);
        int get_slot_number();
        void set_slot_number(int slot_number);

        void park_vehicle(vehicle* vehicle);
        void remove_vehicle();
    private:
        int floor_number;
        int slot_number;
        bool is_empty;
        vehicle* parked_vehicle;
};

class parking_lot {
    public:
        parking_lot(); // generate floors number and slots number randomly
        parking_lot(int floors, int* slots);
        ~parking_lot();
        
        int get_floor_number();
        void set_floor_number(int floor_number);
        int get_slot_number(int floor);
        void set_slot_number(int slot_number, int floor);
        int get_all_slots();
        parking_slot* get_parking_slots();
        
        void park_vehicle(vehicle* vehicle); // park the vehicle in the parking lot
        void park_vehicle(vehicle* vehicle, int floor, int slot); // park the vehicle in a specific floor and slot
        void remove_vehicle(int floor, int slot); // remove the vehicle in a specific floor and slot

        int cal_empty_slot();// find empty slot in the parking lot
        int cal_empty_slot(int floor); // find empty slot in a specific floor

        void print_parking_lot();
        parking_slot* find_empty_slot(); // always find the cloest empty slot , if no empty slot, return nullptr
        void hint(); // print the hint of the parking lot
        void ticket(); // print the ticket of the parking lot
       
    private:
        void set_all_slots(int all_slots);
        int floors;
        int all_slots;
        int* slots;
        parking_slot* parking_slots;
};

#endif