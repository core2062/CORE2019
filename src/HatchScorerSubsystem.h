#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <frc/WPILib.h>

using namespace CORE;
using namespace frc;

class HatchScorerSubsystem : public CORESubsystem {
public:
	HatchScorerSubsystem();
	void robotInit() override; 
	void teleopInit() override;
	void teleop() override;
	void ActuateClaw();
	void SetClawState();
private:
	
	DoubleSolenoid m_solenoidExtend, m_solenoidGrab, m_solenoidRelease;
	
	
};