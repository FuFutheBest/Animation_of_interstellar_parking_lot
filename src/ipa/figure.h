#ifndef __FIGURE_H__
#define __FIGURE_H__

#include <cmath>
#include <utility>

#ifndef HEADLESS
#include <GL/glut.h>
#endif  // HEADLESS

static const float PI = 3.1415926536f;
static const float ALPHA = 0.5;
static const int SEGMENTS = 360;

typedef struct pos {
	int floor;
	int slot;
} Pos;

bool operator==(const Pos &p1, const Pos &p2);

class Vec {
   private:
	float x, y;

   public:
	explicit Vec(float _x = 0, float _y = 0);
	float getX();
	float getY();
	Vec operator+(Vec v);
	Vec operator-(Vec v);
	Vec operator*(float k);
	float operator*(Vec v);
	Vec operator<<(float angle);  // rotating in counter-clockwise
	Vec operator>>(float angle);  // clockwise
};

class Figure {
   private:
	Vec anchor;   // it is the coordinate of the figure
	float angle;  // angle stands for the direction of the figure it self
	float scale;  // scale is the size of the figure
	float r, g, b;

   public:
	Figure();
	virtual void setAnchor(Vec _anchor);
	Vec getAnchor();
	virtual void setAngle(float _angle);
	float getAngle();
	virtual void setScale(float _scale);
	float getScale();
	void setColor(float _r, float _g, float _b);
	float getR();
	float getG();
	float getB();
	virtual void draw() = 0;
	virtual void move(Vec dir);
	virtual void rotate(float _angle);
	virtual void zoom(float k);
	virtual ~Figure();
};

class Circle : public Figure {
   private:
	float radius;

   public:
	explicit Circle(Vec _anchor = Vec(0, 0), float _radius = 1, float _r = 0, float _g = 0,
	                float _b = 0);
	void draw() override;
};

class Rectangle : public Figure {
   private:
	float width, height;

   public:
	explicit Rectangle(Vec _anchor = Vec(0, 0), float _angle = 0, float _width = 1,
	                   float _height = 1, float _r = 0, float _g = 0, float _b = 0);
	void draw() override;
};

class Triangle : public Figure {
   private:
	Vec p1, p2, p3;

   public:
	explicit Triangle(Vec _anchor = Vec(0, 0), float _angle = 0, Vec _p1 = Vec(0, 1),
	                  Vec _p2 = Vec(-0.5, -0.5), Vec _p3 = Vec(0.5, -0.5), float _r = 0,
	                  float _g = 0, float _b = 0);
	void draw() override;
};

class Line : public Figure {
   private:
	Vec p1, p2;

   public:
	explicit Line(Vec _anchor = Vec(0, 0), float _angle = 0, Vec _p1 = Vec(-1, 0),
	              Vec _p2 = Vec(1, 0), float _r = 0, float _g = 0, float _b = 0);
	void draw() override;
};

class Trapezium : public Figure {
   private:
	Vec p1, p2, p3, p4;

   public:
	explicit Trapezium(Vec _anchor = Vec(0, 0), float _angle = 0, Vec _p1 = Vec(-1, 1),
	                   Vec _p2 = Vec(1, 1), Vec _p3 = Vec(0.5, -1), Vec _p4 = Vec(-0.5, -1),
	                   float _r = 0, float _g = 0, float _b = 0);
	void draw() override;
};

class SemiCircle : public Figure {
   private:
	float radius;

   public:
	explicit SemiCircle(Vec _anchor = Vec(0, 0), float _angle = 0, float _radius = 1, float _r = 0,
	                    float _g = 0, float _b = 0);
	void draw() override;
};

class Group : public Figure {
   private:
	int size;
	Figure **figures;

   public:
	Group();
	void setSize(int _size);
	Figure *getFigure(int id);
	void setFigure(int id, Figure *figure);
	void draw() override;
	void move(Vec dir) override;
	void rotate(float _angle) override;
	void zoom(float k) override;
	void setAnchor(Vec _anchor) override;
	void setAngle(float _angle) override;
	void setScale(float _scale) override;
	~Group();
};

#endif  // __FIGURE_H__
