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


//void keyboard(unsigned char key, int x, int y)
//{
//	/* this is the keyboard event handler
//	the x and y parameters are the mouse
//	coordintes when the key was struck */
//	switch (key)
//	{
//	case 'u':
//	case 'U':
//		glRotatef(3.0, 1.0, 0.0, 0.0); /* rotate up */
//		break;
//	case 'd':
//	case 'D':
//		glRotatef(-3.0, 1.0, 0.0, 0.0); /* rotate down */
//		break;
//	case 'l':
//	case 'L':
//		glRotatef(3.0, 0.0, 1.0, 0.0); /* rotate left */
//		break;
//	case 'r':
//	case 'R':
//		glRotatef(-3.0, 0.0, 1.0, 0.0); /* rotate right */
//	}
//	glutPostRedisplay();
//}
