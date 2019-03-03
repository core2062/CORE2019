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
	void ToggleClaw();
	void ScoreHatch();
	void LoadHatch();
	void ExtendPunch();
	void RetractPunch();
	void OpenClaw();
	void CloseClaw();
	bool GetIsScoring();
	bool GetIsLoading();

private:
	COREConstant<double> m_punchSeconds, m_retractSeconds, m_toggleClawSeconds;
	DoubleSolenoid m_solenoidPunchOne, m_solenoidClaw; 
	bool m_isExtended = false;
	bool m_isOpen = false;
	bool m_isScoring = false;
	bool m_isLoading = false;
	bool m_isRetracting = false;
	bool m_isToggling = false;
	CORETimer m_delayTimer;
	void StartTimer();
	double GetTime();

};