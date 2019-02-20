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
	void PunchHatch();
	void ToggleClaw();

private:
	DoubleSolenoid m_solenoidPunchOne, m_solenoidClaw; 
	bool m_isExtended = false;
	bool m_isOpen = false;
	CORETimer m_delayTimer;
	void StartTimer();
	double GetTime();

};