#include "stdafx.h"

int refreshMills = 20;


void changeViewPort(int w, int h)
{
	//glViewport(0, 0, w, h);

	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* note we divide our width by our height to get the aspect ratio */
	gluPerspective(45.0, w / h, 1.0, 400.0);

	/* set initial position */
	glTranslatef(0.0, 0.0, -10.0);

	glMatrixMode(GL_MODELVIEW);

}


void initializeGLUT(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); /* set the background
									  (clearing) color to
									  RGB(0,0,0) -- black */
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);

}


void Loop(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMills, Loop, 0);
}


