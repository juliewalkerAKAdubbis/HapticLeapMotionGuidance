#pragma once

#include "stdafx.h"

using namespace Leap;

class SampleListener : public Listener {
public:
	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	//virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	virtual void onServiceConnect(const Controller&);
	virtual void onServiceDisconnect(const Controller&);
//	virtual void updateFrameInfo(const Controller&);
	virtual void updateFrameInfo(const Controller& controller, Vector &indexPos, Vector &thumbPos, Vector &centerPos);

private:
};

