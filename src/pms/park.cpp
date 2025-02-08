#include "park.h"

#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;

static const double PRICE[] = {0.2f, 0.15f, 0.1f, 0.05f};
static const char *TYPE[] = {"Van", "Car", "Motorcycle", "Bicycle"};

// Floors
Floors::Floors(int _id, int _size) {
	id = _id;
	size = _size;
	for (int i = 0; i < size; i++) slots.push_back(false);
}
int Floors::getSize() { return size; }
bool Floors::isOccupied(int slot_id) { return slots[(size_t)slot_id]; }
void Floors::occupy(int slot_id) { slots[(size_t)slot_id] = true; }
void Floors::vacate(int slot_id) { slots[(size_t)slot_id] = false; }
Floors::~Floors() {}

// Park
Park::Park(int _size) {
	size = _size;
	floors = new Floors[(size_t)size];
	for (int i = 0; i < size; i++) floors[i] = Floors(i, 12 + rand() % 5);
}
Park::Park(const Park &other) : size(other.size) {
	floors = new Floors[(size_t)size];
	for (int i = 0; i < size; i++) floors[i] = other.floors[i];
}
Park &Park::operator=(const Park &other) {
	if (this == &other) return *this;
	delete[] floors;
	size = other.size;
	floors = new Floors[(size_t)size];
	for (int i = 0; i < size; i++) floors[i] = other.floors[i];
	return *this;
}
int Park::getSize() { return size; }
Floors Park::getFloor(int floor_id) { return floors[(size_t)floor_id]; }
Park::~Park() { delete[] floors; }
Pos Park::findSlot() {
    std::vector<Pos> temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < floors[i].getSize(); j++)
			if (!floors[i].isOccupied(j)) {temp.push_back(Pos{i, j});}
    if (temp.empty()) return Pos{-1, -1};
	return temp[(size_t)rand() % temp.size()];
}
void Park::occupy(Pos pos) { floors[pos.floor].occupy(pos.slot); }
void Park::vacate(Pos pos) { floors[pos.floor].vacate(pos.slot); }

// Vehicle
Vehicle::Vehicle(int _id, int _type) : enter_time(0), leave_time(0), pos{-1, -1} {
	id = _id;
	type = _type;
}
double Vehicle::getDuration() { return difftime(leave_time, enter_time); }
double Vehicle::getPrice() { return PRICE[type] * getDuration() / 60.0; }
void Vehicle::enter(time_t _time) { enter_time = _time; }
void Vehicle::leave(time_t _time) { leave_time = _time; }
Pos Vehicle::getPos() { return pos; }
void Vehicle::park(Pos _pos) { pos = _pos; }
void Vehicle::printArrivalTicket(Park *park) {
	cout << "----Arrival Ticket----\n";
	cout << "Vehicle ID: " << id << "\n";
	cout << "Time of arrival: " << ctime(&enter_time);
	cout << "Type: " << TYPE[type] << "\n";
    cout << "Available slots (O is available, X is occupied):\n";
    int max = park->getFloor(0).getSize();
    for (int i = 1; i < park->getSize(); i++) {
        int temp = park->getFloor(i).getSize();
        if (temp > max) max = temp;
    }
    cout << "F\\S";
    for (int i = 0; i < max; i++) cout << std::setw(3) << i;
    cout << "\n";
    for (int i = 0; i < park->getSize(); i++) {
        cout << std::setw(3) << i;
        for (int j = 0; j < park->getFloor(i).getSize(); j++)
            cout << std::setw(3) << (park->getFloor(i).isOccupied(j) ? "X" : "O");
        cout << "\n";
    }
    cout << "\n";
}
void Vehicle::printSlot() {
    cout << "Vehicle " << id << " parked at floor " << pos.floor << " slot " << pos.slot << "\n\n";
}
void Vehicle::printDepartureTicket() {
	cout << "----Departure Ticket----\n";
	cout << "Vehicle ID: " << id << "\n";
	cout << "Duration: " << std::fixed  << std::setprecision(1) << getDuration() / 60.0f << " minutes\n";
	cout << "Type: " << TYPE[type] << "\n";
	cout << "Price: " << std::fixed  << std::setprecision(2) << getPrice() << " dollars\n\n";
}
Vehicle::~Vehicle() {}
