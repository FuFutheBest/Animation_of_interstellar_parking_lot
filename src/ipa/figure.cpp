#include "figure.h"

#include <utility>

bool operator==(const Pos &p1, const Pos &p2) { return p1.floor == p2.floor && p1.slot == p2.slot; }

Vec::Vec(float _x, float _y) : x(_x), y(_y) {}  // Constructor

float Vec::getX() { return x; }
float Vec::getY() { return y; }

Vec Vec::operator+(Vec v) { return Vec(x + v.x, y + v.y); }
Vec Vec::operator-(Vec v) { return Vec(x - v.x, y - v.y); }
Vec Vec::operator*(float k) { return Vec(x * k, y * k); }
float Vec::operator*(Vec v) { return x * v.x + y * v.y; }

Vec Vec::operator<<(float angle) {
	return Vec(x * cosf(angle) - y * sinf(angle), x * sinf(angle) + y * cosf(angle));
}

Vec Vec::operator>>(float angle) {
	return Vec(x * cosf(angle) + y * sinf(angle), -x * sinf(angle) + y * cosf(angle));
}

Figure::Figure() : anchor(0, 0), angle(0), scale(0), r(0), g(0), b(0) {}

void Figure::setAnchor(Vec _anchor) { anchor = _anchor; }
Vec Figure::getAnchor() { return anchor; }

void Figure::setAngle(float _angle) { angle = _angle; }
float Figure::getAngle() { return angle; }

void Figure::setScale(float _scale) { scale = _scale; }
float Figure::getScale() { return scale; }

void Figure::setColor(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
}
float Figure::getR() { return r; }
float Figure::getG() { return g; }
float Figure::getB() { return b; }

void Figure::move(Vec dir) { anchor = anchor + dir; }
void Figure::rotate(float _angle) { angle = fmodf(angle + _angle, 2.0f * PI); }
void Figure::zoom(float k) { scale *= k; }

Figure::~Figure() {}

Circle::Circle(Vec _anchor, float _radius, float _r, float _g, float _b) {
	radius = _radius;
	setAngle(0);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void Circle::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_POLYGON);
	Vec v = Vec(radius, 0) * getScale();
	for (int i = 0; i < SEGMENTS; i++) {
		v = v << (2.0f * PI / SEGMENTS);
		Vec temp = getAnchor() + v;
		glVertex2f(temp.getX(), temp.getY());
	}
	glEnd();
#endif  // HEADLESS
}

Rectangle::Rectangle(Vec _anchor, float _angle, float _width, float _height, float _r, float _g,
                     float _b) {
	width = _width;
	height = _height;
	setAngle(_angle);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void Rectangle::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_POLYGON);
	Vec v = getAnchor() + (Vec(width / 2, height / 2) * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (Vec(width / 2, -height / 2) * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (Vec(-width / 2, -height / 2) * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (Vec(-width / 2, height / 2) * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	glEnd();
#endif  // HEADLESS
}

Triangle::Triangle(Vec _anchor, float _angle, Vec _p1, Vec _p2, Vec _p3, float _r, float _g,
                   float _b)
    : p1(_p1), p2(_p2), p3(_p3) {
	setAngle(_angle);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void Triangle::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_TRIANGLES);
	Vec temp = getAnchor() + (p1 * getScale() << getAngle());
	glVertex2f(temp.getX(), temp.getY());
	temp = getAnchor() + (p2 * getScale() << getAngle());
	glVertex2f(temp.getX(), temp.getY());
	temp = getAnchor() + (p3 * getScale() << getAngle());
	glVertex2f(temp.getX(), temp.getY());
	glEnd();
#endif  // HEADLESS
}

Line::Line(Vec _anchor, float _angle, Vec _p1, Vec _p2, float _r, float _g, float _b)
    : p1(_p1), p2(_p2) {
	setAngle(_angle);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void Line::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_LINES);
	Vec temp = getAnchor() + (p1 * getScale() << getAngle());
	glVertex2f(temp.getX(), temp.getY());
	temp = getAnchor() + (p2 * getScale() << getAngle());
	glVertex2f(temp.getX(), temp.getY());
	glEnd();
#endif  // HEADLESS
}

Trapezium::Trapezium(Vec _anchor, float _angle, Vec _p1, Vec _p2, Vec _p3, Vec _p4, float _r,
                     float _g, float _b)
    : p1(_p1), p2(_p2), p3(_p3), p4(_p4) {  // use to initialise the variables p1, p2, p3, p4
	setAngle(_angle);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void Trapezium::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_POLYGON);
	Vec v = getAnchor() + (p1 * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (p2 * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (p3 * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	v = getAnchor() + (p4 * getScale() << getAngle());
	glVertex2f(v.getX(), v.getY());
	glEnd();
#endif  // HEADLESS
}

SemiCircle::SemiCircle(Vec _anchor, float _angle, float _radius, float _r, float _g, float _b) {
	radius = _radius;
	setAngle(_angle);
	setAnchor(_anchor);
	setScale(1);
	setColor(_r, _g, _b);
}

void SemiCircle::draw() {
#ifndef HEADLESS
	glColor4f(getR(), getG(), getB(), ALPHA);
	glBegin(GL_POLYGON);
	Vec v = Vec(radius, 0) * getScale() << getAngle() >> (PI / 2.0f);
	for (int i = 0; i <= SEGMENTS / 2; i++) {
		if (i) {
			v = v << (2.0f * PI / (float)SEGMENTS);
		}
		Vec temp = getAnchor() + v;
		glVertex2f(temp.getX(), temp.getY());
	}
	glEnd();
#endif  // HEADLESS
}

Group::Group() : size(0), figures(nullptr) {
	Figure::setAngle(0);
	Figure::setAnchor(Vec(0, 0));
	Figure::setScale(1);
	Figure::setColor(0, 0, 0);
}

void Group::setSize(int _size) {
	size = _size;
	figures = new Figure *[(size_t)size];
}

void Group::setFigure(int id, Figure *figure) { figures[id] = figure; }
Figure *Group::getFigure(int id) { return figures[id]; }
void Group::draw() {
	for (int i = 0; i < size; i++) figures[i]->draw();
}
void Group::move(Vec dir) {
	for (int i = 0; i < size; i++) figures[i]->move(dir);
	Figure::move(dir);
}
void Group::rotate(float _angle) {
	for (int i = 0; i < size; i++) {
		figures[i]->rotate(_angle);
		figures[i]->setAnchor(((figures[i]->getAnchor() - getAnchor()) << _angle) + getAnchor());
	}
	Figure::rotate(_angle);
}
void Group::zoom(float k) {
	for (int i = 0; i < size; i++) {
		figures[i]->zoom(k);
		figures[i]->setAnchor((figures[i]->getAnchor() - getAnchor()) * k + getAnchor());
	}
	Figure::zoom(k);
}
void Group::setAnchor(Vec _anchor) { move(_anchor - getAnchor()); }
void Group::setAngle(float _angle) { rotate(_angle - getAngle()); }
void Group::setScale(float _scale) { zoom(_scale / getScale()); }
Group::~Group() {
	for (int i = 0; i < size; i++) delete figures[i];
	delete[] figures;
}
