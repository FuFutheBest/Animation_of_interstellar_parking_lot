#include "figure.h"
Vec::Vec(float _x, float _y) {
  this->x = _x;
  this->y = _y;
}

float Vec::getX() { return this->x; }
float Vec::getY() { return this->y; }

Vec Vec::operator+(const Vec &other) {
  return Vec(this->x + other.x, this->y + other.y);
}
Vec Vec::operator-(const Vec &other) {
  return Vec(this->x - other.x, this->y - other.y);
}

Vec Vec::operator*(const float k) { return Vec(k * this->x, k * this->y); }

Vec Vec::operator/(const float k) { return Vec(this->x / k, this->y / k); }

Vec Vec::operator<<(const float angle) {
  float x1 = this->x * cosf(angle) - this->y * sinf(angle);
  float y1 = this->x * sinf(angle) + this->y * cosf(angle);
  return Vec(x1, y1);
}

Vec Vec::operator>>(const float angle) {
  float x1 = this->x * cosf(angle) + this->y * sinf(angle);
  float y1 = -this->x * sinf(angle) + this->y * cosf(angle);
  return Vec(x1, y1);
}

mycolor get_color(char c) {
  mycolor result;
  switch (c) {
  case 'w':
    result = {1.0f, 1.0f, 1.0f};
    break; // white
  case 'b':
    result = {0.0f, 0.0f, 0.0f};
    break; // black
  case 'r':
    result = {1.0f, 0.0f, 0.0f};
    break; // red
  case 'g':
    result = {0.0f, 1.0f, 0.0f};
    break; // green
  case 'l':
    result = {0.0f, 0.0f, 1.0f};
    break; // blue
  case 'y':
    result = {1.0f, 1.0f, 0.0f};
    break; // yellow
  case 'c':
    result = {0.0f, 1.0f, 1.0f};
    break; // cyan
  case 'm':
    result = {1.0f, 0.0f, 1.0f};
    break; // magenta
  case 'o':
    result = {1.0f, 0.647f, 0.0f};
    break; // orange
  case 'p':
    result = {0.502f, 0.0f, 0.502f};
    break; // purple
  default:
    result = {0.0f, 0.0f, 0.0f};
    break; // default as black
  }
  return result;
}

Figure::Figure(Vec anchor, float angle, float u_length, mycolor color) {
  this->anchor = anchor;
  this->angle = angle;
  this->u_length = u_length;
  this->color = color;
}

Vec Figure::getAnchor() { return this->anchor; }
float Figure::getangle() { return this->angle; }
float Figure::getlen() { return this->u_length; };
mycolor Figure::getcolor() { return this->color; };

void Figure::setAnchor(const Vec a) { this->anchor = a; }
void Figure::setangle(const float angle) { this->angle = angle; }
void Figure::setcolor(mycolor color) { this->color = color; }
void Figure::setlen(float u_length) { this->u_length = u_length; }

void Figure::move(Vec dir) { this->anchor = this->anchor + dir; }
void Figure::rotate(float angle) { this->angle = this->angle + angle; }
void Figure::zoom(float k) { this->u_length = this->u_length * k; }

Circle::Circle(Vec anchor, float angle, float u_length, mycolor color) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
}

void Circle::draw() {
#ifndef HEADLESS
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX(), this->getAnchor().getY());
  for (int i = 0; i <= 3000; i++) {
    float angle = static_cast<float>(2 * M_PI * i / 3000);
    glVertex2f(this->getAnchor().getX() + this->getlen() * cosf(angle),
               this->getAnchor().getY() + this->getlen() * sinf(angle));
  }
  glEnd();
  glFlush();
#endif
}

Semicircle::Semicircle(Vec anchor, float angle, float u_length, mycolor color) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
}

void Semicircle::draw() {
#ifndef HEADLESS
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX(), this->getAnchor().getY());
  for (int i = -1500; i <= 1500; i++) {
    float angle = static_cast<float>(M_PI * i / 3000);
    glVertex2f(this->getAnchor().getX() + this->getlen() * cosf(angle),
               this->getAnchor().getY() + this->getlen() * sinf(angle));
  }
  glEnd();
  glFlush();
#endif
}

Triangle::Triangle(Vec anchor, float angle, float u_length, mycolor color) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
}

void Triangle::draw() {
#ifndef HEADLESS
  glBegin(GL_TRIANGLES);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX() + cosf(this->getangle()) * this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle()) * this->getlen());
  glVertex2f(this->getAnchor().getX() +
                 cosf(this->getangle() + static_cast<float>(2 * M_PI / 3)) *
                     this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle() + static_cast<float>(2 * M_PI / 3)) *
                     this->getlen());
  glVertex2f(this->getAnchor().getX() +
                 cosf(this->getangle() - static_cast<float>(2 * M_PI / 3)) *
                     this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle() - static_cast<float>(2 * M_PI / 3)) *
                     this->getlen());
  glEnd();
  glFlush();
#endif
}

Right_Triangle::Right_Triangle(Vec anchor, float angle, float u_length,
                               mycolor color) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
}

void Right_Triangle::draw() {
#ifndef HEADLESS
  glBegin(GL_TRIANGLES);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX() + cosf(this->getangle()) * this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle()) * this->getlen());
  glVertex2f(this->getAnchor().getX() +
                 cosf(this->getangle() + static_cast<float>(2 * M_PI / 3)) *
                     this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle() + static_cast<float>(2 * M_PI / 3)) *
                     this->getlen());
  glVertex2f(this->getAnchor().getX() +
                 (cosf(this->getangle() + static_cast<float>(2 * M_PI / 3)) +
                  cosf(this->getangle() - static_cast<float>(2 * M_PI / 3))) *
                     this->getlen() / 2,
             this->getAnchor().getY() +
                 (sinf(this->getangle() - static_cast<float>(2 * M_PI / 3)) +
                  sinf(this->getangle() + static_cast<float>(2 * M_PI / 3))) *
                     this->getlen() / 2);
  glEnd();
  glFlush();
#endif
}

Rectangle::Rectangle(Vec anchor, float angle, float u_length, mycolor color,
                     float angle1) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
  this->angle1 = angle1;
}

void Rectangle::setangle1(float a) { this->angle1 = a; }

void Rectangle::draw() {
#ifndef HEADLESS
  glBegin(GL_POLYGON);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX() +
                 cosf(this->getangle() + this->angle1) * this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle() + this->angle1) * this->getlen());
  glVertex2f(this->getAnchor().getX() +
                 cosf(this->getangle() - this->angle1) * this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle() - this->angle1) * this->getlen());
  glVertex2f(this->getAnchor().getX() + cosf(static_cast<float>(M_PI) +
                                             this->getangle() + this->angle1) *
                                            this->getlen(),
             this->getAnchor().getY() + sinf(static_cast<float>(M_PI) +
                                             this->getangle() + this->angle1) *
                                            this->getlen());
  glVertex2f(this->getAnchor().getX() + cosf(static_cast<float>(M_PI) +
                                             this->getangle() - this->angle1) *
                                            this->getlen(),
             this->getAnchor().getY() + sinf(static_cast<float>(M_PI) +
                                             this->getangle() - this->angle1) *
                                            this->getlen());
  glEnd();
  glFlush();
#endif
}

Trapezium::Trapezium(Vec anchor, float angle, float u_length, mycolor color,
                     float ratio, float angle1, float angle2) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
  this->ratio = ratio;
  this->angle1 = angle1;
  this->angle2 = angle2;
}

void Trapezium::setratio(float k) { this->ratio = k; }
void Trapezium::setangle1(float a) { this->angle1 = a; }
void Trapezium::setangle2(float a) { this->angle2 = a; }

void Trapezium::draw() {
#ifndef HEADLESS
  glBegin(GL_POLYGON);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX() + cosf(this->getangle() + this->angle1) *
                                            this->getlen() * this->ratio,
             this->getAnchor().getY() + sinf(this->getangle() + this->angle1) *
                                            this->getlen() * this->ratio);
  glVertex2f(this->getAnchor().getX() + cosf(this->getangle() - this->angle1) *
                                            this->getlen() * this->ratio,
             this->getAnchor().getY() + sinf(this->getangle() - this->angle1) *
                                            this->getlen() * this->ratio);
  glVertex2f(this->getAnchor().getX() + cosf(static_cast<float>(M_PI) +
                                             this->getangle() + this->angle2) *
                                            this->getlen(),
             this->getAnchor().getY() + sinf(static_cast<float>(M_PI) +
                                             this->getangle() + this->angle2) *
                                            this->getlen());
  glVertex2f(this->getAnchor().getX() + cosf(static_cast<float>(M_PI) +
                                             this->getangle() - this->angle2) *
                                            this->getlen(),
             this->getAnchor().getY() + sinf(static_cast<float>(M_PI) +
                                             this->getangle() - this->angle2) *
                                            this->getlen());
  glEnd();
  glFlush();
#endif
}

Line::Line(Vec anchor, float angle, float u_length, mycolor color) {
  setAnchor(anchor);
  setangle(angle);
  setlen(u_length);
  setcolor(color);
}

void Line::draw() {
#ifndef HEADLESS
  glBegin(GL_LINES);
  glColor3f(this->getcolor().r, this->getcolor().g, this->getcolor().b);
  glVertex2f(this->getAnchor().getX() + cosf(this->getangle()) * this->getlen(),
             this->getAnchor().getY() +
                 sinf(this->getangle()) * this->getlen());
  glVertex2f(this->getAnchor().getX() - cosf(this->getangle()) * this->getlen(),
             this->getAnchor().getY() -
                 sinf(this->getangle()) * this->getlen());
  glEnd();
  glFlush();
#endif
}
