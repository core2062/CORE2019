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
	void TogglePunchHatch();
	void openClaw();
	void closeClaw();
	void ExtendPunch();
	void RetractPunch();

private:
	DoubleSolenoid m_solenoidPunchOne, m_solenoidPunchTwo, m_solenoidClaw; 
	bool m_isExtended = false;
	bool m_isOpen = false;
	bool m_isOperating = false;
	bool m_isRetracting = false;
	CORETimer m_delayTimer;
	void StartTimer();
	double GetTime();

};