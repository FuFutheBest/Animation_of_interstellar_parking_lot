#ifndef __PARKING_H__
#define __PARKING_H__

#include <ctime>
#include <iostream>
#include <vector>

typedef struct pos {
	int floor;
	int slot;
} Pos;

class Floors {
   private:
	int id;
	int size;
	std::vector<bool> slots;

   public:
	explicit Floors(int _id = -1, int _size = 0);
	int getSize();
	bool isOccupied(int slot_id);
	void occupy(int slot_id);
	void vacate(int slot_id);
	~Floors();
};

class Park {
   private:
	int size;
	Floors *floors;

   public:
	explicit Park(int _size = 0);
	explicit Park(const Park &other);
	Park &operator=(const Park &other);
	int getSize();
    Floors getFloor(int floor_id);
	Pos findSlot();
	void occupy(Pos pos);
	void vacate(Pos pos);
	~Park();
};

class Vehicle {
   private:
	int id;
	int type;
	time_t enter_time;
	time_t leave_time;
	Pos pos;

   public:
	explicit Vehicle(int _id = -1, int _type = 0);
	double getDuration();
	double getPrice();
	void enter(time_t _time);
	void leave(time_t _time);
	Pos getPos();
	void park(Pos _pos);
	void printArrivalTicket(Park *park);
	void printDepartureTicket();
    void printSlot();
	~Vehicle();
};

#endif  // __PARKING_H__
