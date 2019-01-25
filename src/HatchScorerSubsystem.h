#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;

class HatchScorerSubsystem : public CORESubsystem {
public:
	HatchScorerSubsystem();
	void robotInit();
	void teleopInit();
	void teleop();
	void ActuateClaw();
	void SetClawState();
private:
	
};