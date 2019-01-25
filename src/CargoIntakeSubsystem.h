#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;

class CargoIntakeSubsystem : public CORESubsystem {
public:
	CargoIntakeSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void setIntakeSpeed(double);
	bool isIntaking();
private:
	
};