#include "vehicle.h"

Vehicle::Vehicle() : pos({0, 0}), is_moving(false) {}
void Vehicle::setPos(Pos _pos) { pos = _pos; }
Pos Vehicle::getPos() { return pos; }
bool Vehicle::getIsMoving() { return is_moving; }
void Vehicle::setIsMoving(int _is_moving) { is_moving = _is_moving; }

void Vehicle::park() {
	float y1 = 11.0f + (float)pos.floor * 12.0f, x1 = 0.5f + (float)abs(pos.slot) * 2.0f,
	      y2 = 3.5f * (pos.slot < 0 ? -1 : 1), v = 0.1f;
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
		this->setAngle(PI / 2);
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
		this->rotate(-dtheta);
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
		this->setAngle(0.0f);
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
		this->rotate(dtheta * (y2 > 0 ? -1 : 1));
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
		this->setAngle(PI / 2 * (y2 > 0 ? -1 : 1));
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
void Vehicle::leave() {
	float y1 = 11.0f + (float)pos.floor * 12.0f, x1 = 0.5f + (float)abs(pos.slot) * 2.0f,
	      y2 = 3.5f * (pos.slot < 0 ? -1 : 1), v = 0.1f;
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
		Vec vy(0.0f, (y2 > 0 ? -v : v));              // Determine direction based on y2
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
		this->rotate(dtheta * (y2 > 0 ? -1 : 1));  // Counter-clockwise rotation
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
		this->setAngle(PI);
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
		this->rotate(dtheta);  // Clockwise rotation
		if (current_angle < PI / 2) {
			this->move(vc1);
		} else {
			reverse_circle1 = false;
			reverse_first_step = true;
			current_angle = 0.0f;  // Reset angle
		}
	}

	if (reverse_first_step) {
		Vec vy(0.0f, -v);         // Move straight downward
		this->setAngle(-PI / 2);  // Face downward
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
