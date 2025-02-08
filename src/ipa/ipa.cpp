#include <unistd.h>

#include <ctime>
#include <vector>

#include "park.h"
#include "vehicle.h"

#ifndef HEADLESS
void TimeStep(int n) {
	glutTimerFunc((unsigned)n, TimeStep, n);
	glutPostRedisplay();
}

Vehicle *newVehicle() {
	switch (rand() % 4) {
		case 0:
			return new SpaceCraft;
		case 1:
			return new UFO;
		case 2:
			return new Teleported;
		case 3:
			return new Car;
		default:
			return nullptr;
	}
}

void glDraw() {
	static Park park(3);
	static std::vector<Vehicle *> vehicles;
	static int in_cnt = 10, out_cnt = 50;
	static bool init = true, is_entering = false, is_leaving = false;
	static size_t id = 0;
	int r = rand() % 10;
	if (init) {
		for (int i = 0; i < in_cnt; i++) {
			Vehicle *v = newVehicle();
			v->setPos(park.findSlot());
			float y1 = 7.0f + (float)v->getPos().floor * 12.0f +
			           3.5f * (v->getPos().slot > 0 ? 1 : -1),
			      x1 = 2.0f + (float)abs(v->getPos().slot) * 2.0f;
			v->setAnchor(Vec(x1, y1));
			v->setAngle(PI / 2 * (v->getPos().slot > 0 ? -1 : 1));
			park.occupy(v->getPos());
			vehicles.push_back(v);
		}
		init = false;
	}
	if (is_entering) {
		vehicles[id]->park();
		if (fabsf(vehicles[id]->getAnchor().getY()) <= 3.5) park.openDoor();
		else park.closeDoor();
		if (!vehicles[id]->getIsMoving()) is_entering = false;
	} else if (is_leaving) {
		vehicles[id]->leave();
		if (fabsf(vehicles[id]->getAnchor().getY()) <= 3.5) park.openDoor();
		else park.closeDoor();
		if (!vehicles[id]->getIsMoving()) {
			vehicles.erase(vehicles.begin() + id);
			out_cnt--;
			is_leaving = false;
		}
	} else if ((r > 3 && in_cnt < 50 && park.findSlot().floor != -1) || vehicles.empty()) {
		Vehicle *v = newVehicle();
		v->setPos(park.findSlot());
		v->setAnchor(Vec(1.5f, -4.0f));
		park.occupy(v->getPos());
		vehicles.push_back(v);
		id = vehicles.size() - 1;
		in_cnt++;
		is_entering = true;
		v->setIsMoving(true);
	} else if ((r <= 3 || in_cnt >= 50) && out_cnt > 0) {
		id = (size_t)rand() % vehicles.size();
		Vehicle *v = vehicles[id];
		park.vacate(v->getPos());
		is_leaving = true;
		v->setIsMoving(true);
	} else if (out_cnt <= 0) {
		sleep(2);
		exit(0);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	park.draw();
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		(*it)->feature();
		(*it)->draw();
	}
	glutSwapBuffers();
	glFlush();
}

void glInit() {
	srand((unsigned)time(NULL));
	int argc = 1;
	glutInit(&argc, nullptr);
	glutInitWindowSize(400, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("p3");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 30.0, -10.0, 40.0, -10.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
}
#endif  // HEADLESS

int main() {
#ifndef HEADLESS
	glInit();
	glutDisplayFunc(glDraw);
	glutTimerFunc(25, TimeStep, 25);
	glutMainLoop();
#endif  // HEADLESS
}
