#ifndef __VEHICLE_H__
#define __VEHICLE_H__
class Vehicle {
private:
  figure **body;
  Vec anchor;
  float angle;

public:
  void setAnchor(Vec a);
  void setangle(float a);
  void addFigure(figure *f);
  virtual Vehicle() = 0;
  virtual ~Vehicle() = 0;
  virtual void draw() = 0;
},

    class Car : public Vehicle {
public:
  Car() override;
  ~Car() override;
  void draw() override;
};
#endif // __VEHICLE_H__
