#include "park.h"

#include <algorithm>
#include <vector>

// Floor
Floor::Floor(int _id, int _size, float _lens, float _wids, float _widd, float _height, float dh,
             Vec _opos) {
	id = _id;
	size = _size;
	lens = _lens;
	wids = _wids;
	widd = _widd;
	height = _height;
	deltaheight = dh;
	setAnchor(_opos);
	setSize(5 + 4 * (size / 2));

	// then set the wall beside the door
	Vec p2_5(getAnchor().getX() + widd, getAnchor().getY());
	Vec p3(getAnchor().getX() + widd, getAnchor().getY() + deltaheight);
	setFigure(0, new Line(getAnchor(), 0, p2_5, p3, 0, 0, 0));
	// then the bottom wall
	Vec p4(getAnchor().getX() + widd * 2 + (float)size * lens / 2,
	       getAnchor().getY() + deltaheight);
	setFigure(1, new Line(getAnchor(), 0, p3, p4, 0, 0, 0));
	// the right wall
	Vec p5(getAnchor().getX() + widd * 2 + (float)size * lens / 2,
	       getAnchor().getY() + deltaheight + height);
	setFigure(2, new Line(getAnchor(), 0, p4, p5, 0, 0, 0));
	Vec p6(getAnchor().getX() + widd, getAnchor().getY() + deltaheight + height);
	Vec p7(getAnchor().getX(), getAnchor().getY() + deltaheight + height);
	setFigure(3, new Line(getAnchor(), 0, p5, p6, 0, 0, 0));
	setFigure(4, new Line(getAnchor(), 0, p7, getAnchor(), 0, 0, 0));
	// finish adding the element

	for (int i = 0; i < size / 2; ++i) {
		Vec _p1(getAnchor().getX() + widd + (float)i * lens, getAnchor().getY() + deltaheight);
		Vec _p2(getAnchor().getX() + widd + (float)i * lens,
		        getAnchor().getY() + deltaheight + wids);
		Vec _p3(getAnchor().getX() + widd + (float)i * lens + lens,
		        getAnchor().getY() + deltaheight);
		Vec _p4(getAnchor().getX() + widd + (float)i * lens + lens,
		        getAnchor().getY() + deltaheight + wids);
		setFigure(2 * i + 5, new Line(getAnchor(), 0, _p1, _p2, 0, 0, 0));
		setFigure(2 * i + 6, new Line(getAnchor(), 0, _p3, _p4, 0, 0, 0));
	}

	for (int i = 0; i < size / 2; ++i) {
		Vec _p1(getAnchor().getX() + widd + (float)i * lens,
		        getAnchor().getY() + deltaheight + height);
		Vec _p2(getAnchor().getX() + widd + (float)i * lens,
		        getAnchor().getY() + deltaheight - wids + height);
		Vec _p3(getAnchor().getX() + widd + (float)i * lens + lens,
		        getAnchor().getY() + deltaheight + height);
		Vec _p4(getAnchor().getX() + widd + (float)i * lens + lens,
		        getAnchor().getY() + deltaheight - wids + height);
		setFigure(2 * i + 5 + 2 * (size / 2), new Line(getAnchor(), 0, _p1, _p2, 0, 0, 0));
		setFigure(2 * i + 6 + 2 * (size / 2), new Line(getAnchor(), 0, _p3, _p4, 0, 0, 0));
	}
}
int Floor::getSize() { return size; }

Floor::~Floor() {}

// Park
Park::Park(int _size, Vec _door) {
	size = _size;
	floors = new Floor *[(size_t)size];
	Vec anchor(0, 0);
	door = Line(anchor, 0, _door, anchor, 1, 0, 0);

	float l = 2, dd = 3, ds = 3, h = 10, dh = 2;
	for (int i = 0; i < size; i++) {
		Vec o(0, (float)i * ((h + dh) / 2));
		floors[i] = new Floor(i, 12 + rand() % 6, l, dd, ds, h, dh, o);
		for (int j = 1; j < floors[i]->getSize() / 2; j++) {
			slots.push_back({i, j});
			slots.push_back({i, -j});
		}
	}
	Vec point2 = Vec(0, (float)size * ((h + dh) / 2));
	Vec point3 = Vec(_door.getX(), (float)size * ((h + dh) / 2));
	roof = Line(point2, 0, point3, point2, 0, 0, 0);
}

Park::Park(const Park &other) : size(other.size) {
	floors = new Floor *[(size_t)size];
	for (int i = 0; i < size; i++) floors[i] = other.floors[i];
}
Park &Park::operator=(const Park &other) {
	if (this == &other) return *this;
	delete[] floors;
	size = other.size;
	floors = new Floor *[(size_t)size];
	for (int i = 0; i < size; i++) floors[i] = other.floors[i];
	return *this;
}

void Park::draw() {
	for (int i = 0; i < size; i++) floors[i]->draw();
	door.draw();
	roof.draw();
}

int Park::getSize() { return size; }

Floor *Park::getFloor(int floor_id) { return floors[(size_t)floor_id]; }

void Park::openDoor() {
	if (door.getAngle() < PI / 2) door.rotate(0.1f);
	else door.setAngle(PI / 2);
}
void Park::closeDoor() {
	if (door.getAngle() > 0) door.rotate(-0.1f);
	else door.setAngle(0);
}

Park::~Park() {
	for (int i = 0; i < size; ++i) delete floors[i];
	delete[] floors;
}
Pos Park::findSlot() {
	if (slots.empty()) return {-1, -1};
	return slots[(size_t)rand() % slots.size()];
}
void Park::occupy(Pos pos) {
	auto it = std::find(slots.begin(), slots.end(), pos);
	if (it != slots.end()) slots.erase(it);
}
void Park::vacate(Pos pos) { slots.push_back(pos); }
