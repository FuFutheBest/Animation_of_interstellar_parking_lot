#ifndef __FIGURE_H__
#define __FIGURE_H__
#include <GL/glut.h>

#include <cmath>
#define unit 0.5f

class Vec {
private:
  float x, y;

public:
  explicit Vec(float _x = 0.0f, float _y = 0.0f);
  float getX();
  float getY();
  Vec operator+(const Vec &other);
  Vec operator-(const Vec &other);
  Vec operator*(const float k);
  Vec operator/(const float k);
  Vec operator<<(const float angle); // unit should be radian
  Vec operator>>(const float angle); // unit should be radian
};

typedef struct _color {
  float r;
  float g;
  float b;
} mycolor;

mycolor get_color(char c);

class Figure {
private:
  Vec anchor;     // stand for the position of the figure
  float angle;    // stand for the direction of the figure
  float u_length; // stand for the unit length of the figure
  mycolor color;

public:
  Figure(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
         float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f});
  Vec getAnchor();
  float getangle();
  float getlen();
  mycolor getcolor();
  void setAnchor(const Vec a);
  void setangle(const float angle);
  void setlen(float u_length);
  void setcolor(mycolor color);
  virtual void draw() = 0;
  void move(Vec dir);
  void rotate(float angle); // positive : counter-clockwise
  void zoom(float k);       //  k>1 : zoom in  ;  k<1 : zoom out

  virtual ~Figure() {}
};

class Circle : public Figure {
public:
  explicit Circle(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                  float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f});
  ~Circle() = default;
  void draw() override;
};

class Semicircle : public Circle {
public:
  explicit Semicircle(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                      float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f});
  ~Semicircle() = default;
  void draw() override;
};

class Triangle : public Figure {
public:
  explicit Triangle(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                    float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f});
  ~Triangle() = default;
  void draw() override;
};

class Right_Triangle : public Triangle {
public:
  explicit Right_Triangle(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                          float u_length = unit,
                          mycolor color = {0.0f, 0.0f, 0.f});
  ~Right_Triangle() = default;
  void draw() override;
};

class Rectangle : public Figure {
private:
  float angle1;

public:
  explicit Rectangle(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                     float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f},
                     float angle1 = static_cast<float>(M_PI / 6));
  ~Rectangle() = default;
  void setangle1(float a);
  void draw() override;
};

class Trapezium : public Figure {
private:
  float ratio;
  float angle1, angle2;

public:
  explicit Trapezium(Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
                     float u_length = unit, mycolor color = {0.0f, 0.0f, 0.f},
                     float ratio = 0.5,
                     float angle1 = static_cast<float>(M_PI / 6),
                     float angle2 = static_cast<float>(M_PI / 3));
  ~Trapezium() = default;
  void setratio(float k);
  void setangle1(float a);
  void setangle2(float a);
  void draw() override;
};

#endif //__FIGURE_H__
