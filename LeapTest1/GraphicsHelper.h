#pragma once
#include "stdafx.h"

using namespace Leap;


void changeViewPort(int w, int h);
void initializeGLUT(void);
void Loop(int value);
void keyboard(unsigned char key, int x, int y);
void drawFloor(void); 
void drawFingers(int scaleFactor, float* handOffset, Leap::Vector indexPos, Leap::Vector thumbPos, Leap::Vector centerPos);
void drawFigure8(int step);
void drawTarget(float* target, float* basicOffset);
