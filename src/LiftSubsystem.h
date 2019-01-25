#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;

class LiftSubsystem : public CORESubsystem {
public:
	LiftSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void SetLift(double speed);
	void SetRequestedPosition(double position);
	void SetRequestedSpeed(double speed);
	double GetLiftPosition();
	double GetLiftInches();
	void ResetEncoder();
private:
	
};