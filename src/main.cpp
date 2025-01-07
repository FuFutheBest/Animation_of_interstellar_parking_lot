#include <iostream>
#include "figure.h"

void TimeStep(int n) {
	glutTimerFunc(static_cast<unsigned int>(n), TimeStep, n);
	glutPostRedisplay();
}

void gldraw() {
    static Semicircle c1;
    glClear(GL_COLOR_BUFFER_BIT);
    c1.draw();

	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	(void)argc;  // unused
	(void)argv;
#ifndef HEADLESS
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Interstellar Parking Lot");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(gldraw);
	glutTimerFunc(25, TimeStep, 25);
	glutMainLoop();
#endif
	return 0;
}
