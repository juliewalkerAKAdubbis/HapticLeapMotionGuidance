#include "stdafx.h"

char figure8cues(int &step) {
	/* Use list of trajectory cues and current hand position from the Leap to decide the
	current haptic cue to provide to the user */

	static bool center = false;
	const int nPoints = 16;
	int waitPeriod = 6;

	char cueSeries[nPoints] = { 'j','i','l','m','l','i','j','i','l','i','j','m','j','i','l','i' };

	if ( center == true || step >= (nPoints+ waitPeriod) ) {
		center = false;
		return 'k';
	}
	else {
		++step;
		center = true;		// center after each command
		return cueSeries[step-1];
	}
}


char decideHapticCue(Leap::Vector target, Leap::Vector currentPos, float *handOffset, float *basicOffset) {

	double errorX = (currentPos[0] + handOffset[0]) - (target[0] - basicOffset[0]);
	double errorY = (currentPos[1] + handOffset[1]) - (target[1] - basicOffset[1]);

	if (abs(errorX) > .1 || abs(errorY) > 0.1) {
		fprintf(stderr, "Error    %f     %f \n", errorX, errorY);

		if (abs(errorX) > abs(errorY)) {		// if X error is greater than Y error
			if (errorX > 0) {		
				return 'j';							// go left
			}
			else {
				return 'l';							// go right
			}
		}

		else {
			if (errorY> 0) {						// if Y error is greater than X error
				return 'm';							// go down
			}	
			else {
				return 'i';							// go up
			}
		}

	}
}