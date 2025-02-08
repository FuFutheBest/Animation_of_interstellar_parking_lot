#include <iostream>
#include <vector>

#include "park.h"

static const int MAX = 48;

int main(void) {
	std::cout << "----Program Starts----\n\n";
	srand((unsigned int)time(NULL));
	time_t current_time = time(NULL);
	Park park(4);
	std::vector<Vehicle> vehicles;
	int cnt = 0;
	while (true) {
		current_time += (time_t)(rand() % 180 + 1);
		if ((rand() % 5 || vehicles.empty()) && cnt < MAX) {
			Vehicle vehicle(cnt++, rand() % 4);
			Pos pos = park.findSlot();
			if (pos.floor != -1) {
				vehicle.enter(current_time);
				vehicle.printArrivalTicket(&park);
				vehicle.park(pos);
				park.occupy(pos);
				vehicle.printSlot();
				vehicles.push_back(vehicle);
			} else {
				std::cout << "No slots available\n";
			}
		} else if (!vehicles.empty()) {
			size_t id = (size_t)rand() % vehicles.size();
			Vehicle vehicle = vehicles[id];
			vehicle.leave(current_time);
			vehicle.printDepartureTicket();
			park.vacate(vehicle.getPos());
			vehicles.erase(vehicles.begin() + (std::vector<Vehicle>::difference_type)id);
		}
		if (cnt >= MAX && vehicles.empty()) break;
	}
	std::cout << "----Program Ends----\n";
	return 0;
}
