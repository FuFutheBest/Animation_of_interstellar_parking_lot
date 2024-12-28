#include "parking_lot.h"  
#include "vehicle.h"
#include <iostream>

int main(){
    parking_lot parklot;
    parklot.print_parking_lot();
    std::cin.get();
    vehicle in = generate_vehicle(0);
    parklot.hint();
    int floor = 0, slot = 0;
    if( !(std::cin >> floor) ){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, please enter a number" << std::endl;
        exit(1);
    }
    if( !(std::cin >> slot) ){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, please enter a number" << std::endl;
        exit(1);
    }
    parklot.park_vehicle(&in, floor, slot);
    parklot.print_parking_lot();

        
}