#include "vehicle.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

Vehicle::Vehicle(int figure_num, Vec anchor, float angle, float u_length) {
  this->figure_num = figure_num;
  this->anchor = anchor;
  this->angle = angle;
  this->u_length = u_length;
  this->body = new Figure *[figure_num];
}

Vehicle::~Vehicle() {
  for (int i = 0; i < this->figure_num; i++) {
    delete body[i];
  }
  delete[] body;
}

void Vehicle::setAnchor(Vec a) { this->anchor = a; }

void Vehicle::setangle(float a) { this->angle = a; }

void Vehicle::setlen(float u_length) { this->u_length = u_length; }

void Vehicle::addFigure(int rank, Figure *f) {
  if (rank < 0 || rank >= this->figure_num) {
    std::cerr << "Invalid rank" << std::endl;
    exit(-1);
  }
  this->body[rank] = f;
}

Vec Vehicle::getAnchor() { return this->anchor; }

float Vehicle::getangle() { return this->angle; }

float Vehicle::getlen() { return this->u_length; }

void Vehicle::draw() {
  for (int i = 0; i < this->figure_num; i++) {
    this->body[i]->draw();
  }
}

Car::Car() : Vehicle(4) {
  float angle1 = static_cast<float>(M_PI / 10);
  /* window */
  Vec A1 = this->getAnchor() +
           (Vec(this->getAnchor().getX(),
                2 * this->getlen() * sinf(static_cast<float>(angle1)))
            << this->getangle());
  this->addFigure(
      0, new Trapezium(A1, this->getangle() + static_cast<float>(M_PI / 2),
                       this->getlen(), get_color('p'), 0.5,
                       static_cast<float>(M_PI / 3),
                       static_cast<float>(M_PI / 3)));

  /* body */
  this->addFigure(1, new Rectangle(this->getAnchor(), this->getangle(),
                                   this->getlen(), get_color('y'), angle1));

  /* wheels */
  Vec A2 = this->getAnchor() +
           (Vec(this->getAnchor().getX() + this->getlen() / 3,
                -(this->getlen() * sinf(static_cast<float>(angle1)) +
                  (this->getlen() / 5)))
            << this->getangle());
  Vec A3 = this->getAnchor() +
           (Vec(this->getAnchor().getX() - this->getlen() / 3,
                -(this->getlen() * sinf(static_cast<float>(angle1)) +
                  (this->getlen() / 5)))
            << this->getangle());

  this->addFigure(
      2, new Circle(A2, this->getangle(), this->getlen() / 5, get_color('o')));
  this->addFigure(
      3, new Circle(A3, this->getangle(), this->getlen() / 5, get_color('o')));
}
