#include "stdafx.h"

char decideHapticCue(int &step, const int nSteps) {
	/* Use list of trajectory cues and current hand position from the Leap to decide the
	current haptic cue to provide to the user */

	static bool center = false;
	const int nPoints = 16;
	int waitPeriod = 6;

	char cueSeries[nPoints] = { 'j','i','l','m','l','i','j','i','l','i','j','m','j','i','l','i' };

	if (step < waitPeriod || center == true || step >= nPoints) {
		return 'm';
		center = false;
	}
	else {

		return cueSeries[step - waitPeriod];
		step++;
		center = true;		// center after each command
	}
}