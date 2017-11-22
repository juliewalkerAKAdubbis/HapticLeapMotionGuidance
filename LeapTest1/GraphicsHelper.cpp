#include "stdafx.h"

int refreshMills = 20;


void changeViewPort(int w, int h)
{

	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* note we divide our width by our height to get the aspect ratio */
	gluPerspective(45.0, w / h, 1.0, 400.0);

	/* set initial position */
	//glTranslatef(0.0, -10.0, 10.0);

	//glMatrixMode(GL_MODELVIEW);

}


void initializeGLUT(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); /* set the background color to black*/
	glClearDepth(1.0f); // Set background depth to farthest
	//glTranslatef(0.0, -10.0, 10.0);	// Camera Position 

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
	//gluLookAt(0.0, 5, 5, 0.0, 0.0, 0.0, 0.0, 1, 0.0);

}


void Loop(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMills, Loop, 0);
}


void drawFloor(void) {
	/* draw the floor */

	glLoadIdentity();
	glTranslatef(0.0f, -10.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.7f, 0.2f);
	glVertex3f(-100, 0, -100.0);
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(-100.0, 0.0, 100.0);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(100.0, 0.0, 100.0);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex3f(100.0, 0.0, -100.0);
	glEnd();
}


void drawFingers(int scaleFactor, float* handOffset, Leap::Vector indexPos, Leap::Vector thumbPos, Leap::Vector centerPos) {

	// Draw fingers
	glLoadIdentity();
	glTranslatef(handOffset[0], handOffset[1], handOffset[2]);
	glBegin(GL_LINE_STRIP);
	glVertex3f(indexPos[0] / scaleFactor, indexPos[1] / scaleFactor, indexPos[2] / scaleFactor);
	glVertex3f(centerPos[0] / scaleFactor, centerPos[1] / scaleFactor, centerPos[2] / scaleFactor);
	glVertex3f(thumbPos[0] / scaleFactor, thumbPos[1] / scaleFactor, thumbPos[2] / scaleFactor);
	glEnd();

	// Draw end points
	glLoadIdentity();
	glTranslatef(handOffset[0], handOffset[1], handOffset[2]);
	glTranslatef(centerPos[0] / scaleFactor, centerPos[1] / scaleFactor, centerPos[2] / scaleFactor);
	glutSolidSphere(0.25f, 10, 10);

	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(handOffset[0], handOffset[1], handOffset[2]);
	glTranslatef(indexPos[0] / scaleFactor, indexPos[1] / scaleFactor, indexPos[2] / scaleFactor);
	glutSolidSphere(0.15f, 8, 8);

	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(handOffset[0], handOffset[1], handOffset[2]);
	glTranslatef(thumbPos[0] / scaleFactor, thumbPos[1] / scaleFactor, thumbPos[2] / scaleFactor);
	glutSolidSphere(0.15f, 8, 8);


}


void drawFigure8(int step) {

	float basicOffset[3] = { 0.0f, 3.0f, -20.0f };
	int numPoints = 16;
	float t;

	for (int i = 0; i < numPoints; i++) {
		t = 2 * PI / numPoints * i + PI/2;
		glLoadIdentity();
		glTranslatef(basicOffset[0], basicOffset[1], basicOffset[2]);
		glTranslatef(5*cos(t), -3*sin(2*t), 0);

		if (i == step){
			glColor3f(0.25f, 0.0f, 0.5f);
		}
		else {
			glColor3f(0.0f, 0.25f, 0.5f);
		}

		glutSolidSphere(0.25f, 10, 10);

	}

}

void drawTarget(Leap::Vector target, float* basicOffset) {


	glLoadIdentity();
	glTranslatef(basicOffset[0], basicOffset[1], basicOffset[2]);
	glTranslatef(target[0], target[1], target[2]);
	glutSolidSphere(0.25f, 10, 10);

}