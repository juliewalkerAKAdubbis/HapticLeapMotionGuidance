// LeapTest1.cpp : 
// This code interfaces with the Leap Motion tracking device and a haptic device through the serial port.
// Upload Arduino sketch LeapGuidanceSkinDeformation
// Use the Keyboard to provide haptic guidance cues to the user.


#include "stdafx.h"



using namespace std;
using namespace Leap;

// PROTOTYPES -----------------------------------------------------------
void render();
void keyboard(unsigned char key, int x, int y);
int initializeSerialPort(void);
//-----------------------------------------------------------------------



// Create a sample listener and controller for Leap Motion
SampleListener listener;
Controller controller;

// Create Serial Port to communicate with Arduino
HANDLE hSerial;


void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	Leap::Vector indexPos;
	Leap::Vector thumbPos;
	Leap::Vector centerPos;

	// call updates to positions of fingers, passed by reference
	listener.updateFrameInfo(controller, indexPos, thumbPos, centerPos);
	int scaleFactor = 20;

	glLoadIdentity();
	glTranslatef(0.0f, -5.0f, 0.0f);
	drawFloor();
	//glutSolidTorus(1.0f, 1.5f, 20, 20);

	float handOffset[3] = { 0.0f, -5.0f,-20.0f };


	drawFingers(scaleFactor, handOffset, indexPos, thumbPos, centerPos);
	drawTrajectory();



	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{

	/* this is the keyboard event handler
	the x and y parameters are the mouse
	coordintes when the key was struck */

	// Test to serial port
	char commandToSend[1];
	DWORD bytes_written = 0;

	switch (key)
	{
		// Camera commands for graphics window
	case 'w':
	case 'W':
		glRotatef(3.0, 1.0, 0.0, 0.0); /* rotate up */
		break;
	case 's':
	case 'S':
		glRotatef(-3.0, 1.0, 0.0, 0.0); /* rotate down */
		break;
	case 'a':
	case 'A':
		glRotatef(3.0, 0.0, 1.0, 0.0); /* rotate left */
		break;
	case 'd':
	case 'D':
		glRotatef(-3.0, 0.0, 1.0, 0.0); /* rotate right */
		break;
	case 'q':
	case 'Q':
		glutLeaveMainLoop();
		break;


		// Serial communication commands
	case 'i':			/* Push up */
	case 'I':	
		commandToSend[0] = 'i'; //105;
		break;
	case 'm':			/* Push down */
	case 'M':
		commandToSend[0] = 'm'; //107;
		break;
	case 'l':			/* Twist CCW */
	case 'L':
		commandToSend[0] = 'l'; //108;
		break;
	case 'j':			/* Twist CW */
	case 'J':
		commandToSend[0] = 'j'; //106;
		break;
	case 'k':			/* Center */
	case 'K':
		commandToSend[0] = 'k'; //107;
		break;
	default:
		commandToSend[0] = '0';
		break;

	}

	// Send specified text (remaining command line arguments)
	//fprintf(stderr, "Sending bytes...");
	if (!WriteFile(hSerial, commandToSend, 1, &bytes_written, NULL))
	{
		fprintf(stderr, "Error\n");
		CloseHandle(hSerial);
	}
	//fprintf(stderr, "%d bytes written\n", bytes_written);


	glutPostRedisplay();
}

int initializeSerialPort(void) {

	// Declare variables and structures
	//HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	// Open the highest available serial port number
	fprintf(stderr, "Opening serial port...");
	hSerial = CreateFile(
		L"\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	else fprintf(stderr, "OK\n");

	// Set device parameters (38400 baud, 1 start bit,
	// 1 stop bit, no parity)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error getting device state\n");
		CloseHandle(hSerial);
		return 1;
	}

	dcbSerialParams.BaudRate = CBR_115200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (SetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error setting device parameters\n");
		CloseHandle(hSerial);
		return 1;
	}

	// Set COM port timeout settings
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (SetCommTimeouts(hSerial, &timeouts) == 0)
	{
		fprintf(stderr, "Error setting timeouts\n");
		CloseHandle(hSerial);
		return 1;
	}

	Sleep(2000);
	return 0;
}


int main(int argc, char* argv[]) {


		// Set up serial port connection to arduino

	if (initializeSerialPort()) {
		printf("Error Initializing Seruial Port");
	}



//		printf("Adjust the Index Finger Center Position. \nPress k to lower \npress i to raise \nPress Enter when done\n\n");


	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Hello,GL"
	glutCreateWindow("User Interface");
	 
	initializeGLUT();

	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);
	glutTimerFunc(0, Loop, 0);
	glutKeyboardFunc(keyboard); 

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}


	// Output directions to user
	fprintf(stderr, "Press IJKL to direct haptic cues to the user.\nPress Q to exit.");

	// Start the graphics loop
	glutMainLoop();

	// Remove the sample listener when done
	controller.removeListener(listener);


		// Close serial port
	fprintf(stderr, "Closing serial port...");
	if (CloseHandle(hSerial) == 0)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	fprintf(stderr, "OK\n");



	return 0;
}