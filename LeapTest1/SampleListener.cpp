#include "stdafx.h"
//#include "SampleListener.h"

using namespace Leap;

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
const std::string stateNames[] = { "STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END" };

void SampleListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void SampleListener::updateFrameInfo(const Controller& controller, Vector &indexPos, Vector &thumbPos, Vector &centerPos) {
	const Frame frame = controller.frame();
	HandList hands = frame.hands();
	Leap::Hand hand = hands[0];

	//for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		//const Hand hand = *hl;

		// Get fingers of first hand
		const FingerList fingers = hand.fingers();

		//FingerList::const_iterator thumbIter = fingers.begin();
		Finger thumb = fingers[0];
		Finger index = fingers[1];


		indexPos = index.tipPosition();
		thumbPos = thumb.tipPosition();

		Leap::Bone::Type proximal = static_cast<Leap::Bone::Type>(1);
		Bone indexProximal = index.bone(proximal);
		centerPos = indexProximal.prevJoint();


		//std::cout << "index end: " << index.stabilizedTipPosition() << std::endl;
		//std::cout << "thumb end: " << thumb.stabilizedTipPosition() << std::endl;

	//}
}



//void SampleListener::onFrame(const Controller& controller) {
//
//	glutPostRedisplay();
//
//}

//
//
//void SampleListener::onFrame(const Controller& controller) {
//	// Get the most recent frame and report some basic information
//	const Frame frame = controller.frame();
//
//	HandList hands = frame.hands();
//	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
//		// Get the first hand
//		const Hand hand = *hl;
//		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
//		std::cout << std::string(2, ' ') << handType << ", id: " << hand.id() << std::endl;
//		std::cout << "palm position: " << hand.palmPosition() << std::endl;
//		// Get the hand's normal vector and direction
//		const Vector normal = hand.palmNormal();
//		const Vector direction = hand.direction();
//
//		//// Calculate the hand's pitch, roll, and yaw angles
//		//std::cout << std::string(2, ' ') << "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
//		//	<< "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
//		//	<< "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
//
//
//		// Get fingers
//		const FingerList fingers = hand.fingers();
//
//		//FingerList::const_iterator thumbIter = fingers.begin();
//		Finger thumb = fingers[0];
//		Finger index = fingers[1];
//
//
//		std::cout << ",    thumb end: " << thumb.tipPosition();
//		std::cout << ",    index end: " << index.tipPosition();
//
//
//		//for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
//		//	const Finger finger = *fl;
//		//	std::cout << std::string(4, ' ') << fingerNames[finger.type()]
//		//		<< " finger, id: " << finger.id();
//
//		//	// Get finger bones
//		//	for (int b = 0; b < 4; b+=3) {
//		//		Bone::Type boneType = static_cast<Bone::Type>(b);
//		//		Bone bone = finger.bone(boneType);
//		//		std::cout << std::string(6, ' ') << boneNames[boneType]
//		//			<< " bone, start: " << bone.prevJoint()
//		//			<< ", end: " << bone.nextJoint()
//		//			<< ", direction: " << bone.direction() << std::endl;
//		//	}
//		//}
//	}
//
//
//}

void SampleListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void SampleListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}