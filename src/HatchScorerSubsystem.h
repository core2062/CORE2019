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
	void ScoreHatch();
	void LoadHatch();
	void OpenClaw();
	void CloseClaw();
	void ToggleClaw();
	void ExtendPunch();
	void RetractPunch();
	bool GetIsOperating();

private:
	DoubleSolenoid m_solenoidPunchOne, m_solenoidClaw; 
	bool m_isExtended = false;
	bool m_isOpen = false;
	bool m_isOperating = false;
	bool m_isRetracting = false;
	CORETimer m_delayTimer;
	void StartTimer();
	double GetTime();
	COREConstant<double> m_punchSeconds, m_retractSeconds;

};