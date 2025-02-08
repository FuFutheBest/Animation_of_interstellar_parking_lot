#include "vehicle.h"

#include <ctime>

Car::Car(float w, float h) {
	setPos({-1, -1});
	setSize(4);
	setIsMoving(false);
	Vec p = getAnchor();

	// Initialize the body as a rectangle
	setFigure(0, new Rectangle(p, getAngle(), w, h, 1.0f, 0.65f, 0.0f));

	// Initialize the top as a trapezium
	Vec pt0 = Vec(getAnchor().getX(), getAnchor().getY() + h / 4);
	Vec pt1 = pt0 + Vec(-w / 8, h);
	Vec pt2 = pt0 + Vec(w / 8, h);
	Vec pt3 = pt0 + Vec(w / 4, 0);
	Vec pt4 = pt0 + Vec(-w / 4, 0);
	setFigure(1, new Trapezium(pt0, getAngle(), pt1, pt2, pt3, pt4, 0.0f, 0.1f, 0.8f));

	// Initialize the wheels as circles
	Vec p1 = Vec(getAnchor().getX() - w / 4, getAnchor().getY() - h / 2);
	Vec p2 = Vec(getAnchor().getX() + w / 4, getAnchor().getY() - h / 2);
	setFigure(2, new Circle(p1, h / 3, 1.0f, 0.27f, 0.0f));
	setFigure(3, new Circle(p2, h / 3, 1.0f, 0.27f, 0.0f));
}

void Car::feature() {}

Teleported::Teleported(float w, float h) : last_time(time(NULL)) {
	setPos({-1, -1});
	setSize(1);
	setIsMoving(false);
	setColor((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX,
	         (float)rand() / (float)RAND_MAX);
	setFigure(0, new Rectangle(getAnchor(), getAngle(), w, h, getR(), getG(), getB()));
	setAngle(PI / 2);
}

void Teleported::park() {
	float y1 = 7.0f + (float)getPos().floor * 12.0f + 3.5f * (getPos().slot > 0 ? 1 : -1),
	      x1 = 2.0f + (float)abs(getPos().slot) * 2.0f;
	setAnchor(Vec(x1, y1));
	setIsMoving(false);
}
void Teleported::leave() {
	setAnchor(Vec(1.5f, -2.0f));
	setIsMoving(false);
}
void Teleported::feature() {
	if (time(NULL) != last_time) {
		getFigure(0)->setColor((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX,
		                       (float)rand() / (float)RAND_MAX);
		last_time = time(NULL);
	}
}

UFO::UFO(float w, float h) {
	setPos({-1, -1});
	setSize(5);
	setIsMoving(false);
	Vec p = getAnchor();

	// initialize the body of the UfO
	setFigure(0, new SemiCircle(p, 1.57f, w / 2, 0.0f, 0.5f, 1.0f));

	// initialize the feet of the UFO
	Vec p1 = p + Vec(-w / 4, -h / 2);
	Vec p2 = p + Vec(w / 4, -h / 2);
	setFigure(1, new Rectangle(p1, getAngle(), w / 4, h, 0.5f, 0.0f, 0.0f));
	setFigure(2, new Rectangle(p2, getAngle(), w / 4, h, 0.5f, 0.0f, 0.0f));

	// initialize the two lines of the UFO
	Vec pl1 = p + Vec(w / 4, 1.732f * w / 4);
	Vec pl2 = p + Vec(-w / 4, 1.732f * w / 4);
	Vec pl3 = pl1 * 1.5f;
	Vec pl4 = pl2 * 1.5f;
	setFigure(3, new Line(p, getAngle(), pl1, pl3, 0.0f, 0.0f, 0.0f));
	setFigure(4, new Line(p, getAngle(), pl2, pl4, 0.0f, 0.0f, 0.0f));
}

void UFO::feature() { rotate(0.1f); }

SpaceCraft::SpaceCraft(float w, float h) : flag(true), cnt(0) {
	setPos({-1, -1});
	setSize(8);
	setIsMoving(false);
	Vec p = getAnchor();

	// the main body is a rectangle
	setFigure(0, new Rectangle(p, getAngle(), h, w, 1.0f, 1.0f, 0.0f));

	// the head is a triangle
	Vec p1 = p + Vec(h / 2, -w / 2);
	Vec p2 = p + Vec(h / 2, w / 2);
	Vec p3 = p + Vec(h / 2 + 0.866f * w, 0);
	setFigure(1, new Triangle(p, getAngle(), p1, p2, p3, 0.6f, 1.0f, 0.6f));

	// the three rectangles in the main body
	Vec pr1 = p + Vec(0.3f * h, -0.3f * w);
	Vec pr2 = p + Vec(0.3f * h, 0.3f * w);
	Vec pr3 = p + Vec(0.2f * h, 0);
	setFigure(2, new Rectangle(pr3, getAngle(), h / 7, w / 5, 0.5f, 0.8f, 1.0f));
	setFigure(3, new Rectangle(pr1, getAngle(), h / 18, w / 7, 0.5f, 0.8f, 1.0f));
	setFigure(4, new Rectangle(pr2, getAngle(), h / 18, w / 7, 0.5f, 0.8f, 1.0f));

	// the two sides are triangles
	Vec pt11 = p + Vec(0, -w / 2);
	Vec pt12 = p + Vec(-h / 2, -w / 2);
	Vec pt13 = pt12 + Vec(0, -w / 2);
	Vec pt21 = p + Vec(0, w / 2);
	Vec pt22 = p + Vec(-h / 2, w / 2);
	Vec pt23 = pt22 + Vec(0, w / 2);
	setFigure(5, new Triangle(p, getAngle(), pt11, pt12, pt13, 1.0f, 0.65f, 0.3f));
	setFigure(6, new Triangle(p, getAngle(), pt21, pt22, pt23, 1.0f, 0.65f, 0.3f));

	// the base is a trapezium
	Vec pm1 = p + Vec(-h / 2, -0.4f * w);
	Vec pm2 = p + Vec(-h / 2, 0.4f * w);
	Vec pm3 = pm1 + Vec(-h / 8, -0.1f * w);
	Vec pm4 = pm2 + Vec(-h / 8, 0.1f * w);
	setFigure(7, new Trapezium(p, getAngle(), pm1, pm2, pm4, pm3, 0.0f, 0.0f, 0.0f));
}

void SpaceCraft::feature() {
	if (flag) {
		zoom(0.99f);
		cnt++;
	} else {
		zoom(1.01f);
		cnt--;
	}
	if (cnt == 50)
		flag = false;
	else if (cnt == 0)
		flag = true;
}

void UFO::park() {
	float y1 = 11.0f + (float)getPos().floor * 12.0f, x1 = 0.5f + (float)abs(getPos().slot) * 2.0f,
	      y2 = 3.5f * (getPos().slot < 0 ? -1 : 1), v = 0.1f;
	static Vec init_pos = this->getAnchor();
	static bool doing_first_step = true, circle1 = false, doing_second_step = false,
	            circle2 = false, doing_third_step = false, pos_set = false;
	static float current_angle = 0.0f;
	float dtheta = 0.1f;
	float R = 1.0f;
	if (pos_set) {
		init_pos = this->getAnchor();
		pos_set = false;
	}
	if (doing_first_step) {
		Vec vy(0.0f, v);
		if (fabsf(this->getAnchor().getY() - (init_pos.getY() + y1 - R)) > 0.1f) {
			this->move(vy);
		} else {
			doing_first_step = false;
			circle1 = true;
		}
	}

	if (circle1) {
		current_angle += dtheta;
		Vec vc1 = Vec(0, v) >> current_angle;
		if (current_angle < PI / 2) {
			this->move(vc1);
		} else {
			circle1 = false;
			doing_second_step = true;
			current_angle = 0.0f;
		}
	}

	if (doing_second_step) {
		Vec vx(v, 0.0f);
		if (fabsf(this->getAnchor().getX() - (init_pos.getX() + x1 + R)) > 0.1f) {
			this->move(vx);
		} else {
			doing_second_step = false;
			circle2 = true;
		}
	}

	if (circle2) {
		current_angle += dtheta;
		Vec vc2;
		if (y2 > 0)
			vc2 = Vec(-v, 0) >> current_angle;
		else
			vc2 = Vec(-v, 0) << current_angle;
		if (current_angle < PI / 2) {
			this->move(vc2);
		} else {
			circle2 = false;
			doing_third_step = true;
			current_angle = 0.0f;
		}
	}

	if (doing_third_step) {
		Vec vy(0.0f, (y2 > 0 ? v : -v));
		if (fabsf(this->getAnchor().getY() - (init_pos.getY() + y1 + y2)) > 0.1f) {
			this->move(vy);
		} else {
			doing_first_step = pos_set = true;
			circle1 = doing_second_step = circle2 = doing_third_step = false;
			current_angle = 0.0f;
			doing_third_step = false;
			setIsMoving(false);
		}
	}
}
void UFO::leave() {
	float y1 = 11.0f + (float)getPos().floor * 12.0f, x1 = 0.5f + (float)abs(getPos().slot) * 2.0f,
	      y2 = 3.5f * (getPos().slot < 0 ? -1 : 1), v = 0.1f;
	static Vec final_pos = this->getAnchor();  // Dynamically retrieve the current anchor position
	static bool reverse_third_step = true, reverse_circle2 = false, reverse_second_step = false,
	            reverse_circle1 = false, reverse_first_step = false, pos_set = false;
	static float current_angle = 0.0f;
	float dtheta = 0.1f;
	float R = 1.0f;  // Radius of the circular path
	if (pos_set) {
		final_pos = this->getAnchor();
		pos_set = false;
	}
	if (reverse_third_step) {
		Vec vy(0.0f, (y2 > 0 ? -v : v));  // Determine direction based on y2
		if (fabsf(this->getAnchor().getY() - (final_pos.getY() - y2 + R * (y2 > 0 ? 1 : -1))) >
		    0.1f) {
			this->move(vy);
		} else {
			reverse_third_step = false;
			reverse_circle2 = true;
		}
	}

	if (reverse_circle2) {
		current_angle += dtheta;  // Accumulate rotation angle
		Vec vc2;
		if (y2 > 0)
			vc2 = Vec(0, -v) >> current_angle;
		else
			vc2 = Vec(0, v) << current_angle;
		if (current_angle < PI / 2) {
			this->move(vc2);
		} else {
			reverse_circle2 = false;
			reverse_second_step = true;
			current_angle = 0.0f;  // Reset angle
		}
	}

	if (reverse_second_step) {
		Vec vx(-v, 0.0f);
		if (fabsf(this->getAnchor().getX() - (final_pos.getX() - x1 + R)) > 0.1f) {
			this->move(vx);
		} else {
			reverse_second_step = false;
			reverse_circle1 = true;
		}
	}

	if (reverse_circle1) {
		current_angle += dtheta;
		Vec vc1 = Vec(-v, 0) << current_angle;
		if (current_angle < PI / 2) {
			this->move(vc1);
		} else {
			reverse_circle1 = false;
			reverse_first_step = true;
			current_angle = 0.0f;  // Reset angle
		}
	}

	if (reverse_first_step) {
		Vec vy(0.0f, -v);  // Move straight downward
		if (fabsf(this->getAnchor().getY() - (final_pos.getY() - y1 - y2)) > 0.1f) {
			this->move(vy);
		} else {
			reverse_third_step = pos_set = true;
			reverse_circle2 = reverse_second_step = reverse_circle1 = reverse_first_step = false;
			current_angle = 0.0f;
			reverse_first_step = false;  // All steps complete
			setIsMoving(false);
		}
	}
}
