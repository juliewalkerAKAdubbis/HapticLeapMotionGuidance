#pragma once
#include "stdafx.h"

using namespace Leap;

// Prototypes
char  figure8cues(int &step);
char decideHapticCue(Leap::Vector target, Leap::Vector currentPos, float *handOffset, float *basicOffset);