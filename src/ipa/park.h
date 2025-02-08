#ifndef __PARK_H__
#define __PARK_H__

#include <vector>

#include "figure.h"

class Floor : public Group {
   private:
	int id;
	int size;
	// length of a slot
	float lens;
	// width of a slot
	float wids;
	// width of a door
	float widd;
	// height of a floor
	float height;
	// delta height of the corner
	float deltaheight;
	Vec door;

   public:
	explicit Floor(int _id = -1, int _size = 0, float _lens = 0, float _wids = 0, float _widd = 0,
	               float _height = 0, float dh = 0, Vec _opos = Vec(0, 0));
	int getSize();
	~Floor();
};

class Park {
   private:
	int size;
	Floor **floors;
	Line door;
	Line roof;
	std::vector<Pos> slots;

   public:
	explicit Park(int _size = 0, Vec door = Vec(3, 0));
	explicit Park(const Park &other);
	Park &operator=(const Park &other);
	void openDoor();
	void closeDoor();
	void draw();
	int getSize();
	Floor *getFloor(int floor_id);
	Pos findSlot();
	void occupy(Pos pos);
	void vacate(Pos pos);
	~Park();
};

#endif  // __PARK_H__
