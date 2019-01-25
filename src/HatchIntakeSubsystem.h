#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;

class HatchIntakeSubsystem : public CORESubsystem {
public:
	HatchIntakeSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void SetIntakeWheelSpeed(double speed);
	void ActuateHatchIntake();
	bool GetHatchState();
private:
	
};