#ifndef __VEHICLE_H__
#define __VEHICLE_H__
#include "figure.h"
class Vehicle {
private:
  Figure **body;
  int figure_num;
  Vec anchor;
  float angle;
  float u_length;

protected:
  void setAnchor(Vec a);
  void addFigure(int rank, Figure *f);
  void setlen(float u_length);

public:
  Vehicle(int figure_num = 1, Vec anchor = Vec{0.0f, 0.0f}, float angle = 0.0f,
          float u_length = unit);
  ~Vehicle();

  void setangle(float a);

  Vec getAnchor();
  float getangle();
  float getlen();

  void draw();
};

class Car : public Vehicle {
public:
  Car();
  Car(Vec anchor, float angle);
};
#endif // __VEHICLE_H__
