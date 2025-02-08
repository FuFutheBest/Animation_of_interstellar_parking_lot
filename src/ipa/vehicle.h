#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include <ctime>

#include "figure.h"

class Vehicle : public Group {
   public:
	Vehicle();
   void setPos(Pos _pos);
	Pos getPos();
   virtual void park();
   virtual void leave();
   bool getIsMoving();
   void setIsMoving(int _size);
   virtual void feature() = 0;

   private:
	Pos pos;
   bool is_moving;
};

class Car : public Vehicle {
   public:
	explicit Car(float w = 2.5f, float h = 0.5f);
   void feature() override;
};

class Teleported : public Vehicle {
   private:
   time_t last_time;
   public:
	explicit Teleported(float w = 2.5f, float h = 1.25f);
   void park() override;
   void leave() override;
   void feature() override;
};

class UFO : public Vehicle {
   public:
	explicit UFO(float w = 2.0f, float h = 0.2f);
   void park() override;
   void leave() override;
   void feature() override;
};

class SpaceCraft : public Vehicle {
   private:
   bool flag;
   int cnt;
   public:
	explicit SpaceCraft(float w = 0.75f, float h = 3.0f);
   void feature() override;
};

#endif  // __VEHICLE_H__
