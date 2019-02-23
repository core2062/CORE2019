#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <COREUtilities/COREConstant.h>


using namespace CORE;
using namespace frc;

enum class IntakeState
{
	UP = 0,
	DOWN = 1,
	IN = 2,
	OUT = 3
};

class HatchIntakeSubsystem : public CORESubsystem {
public:
	HatchIntakeSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void SetIntake(IntakeState wheelDirection, IntakeState actuator);
	bool HatchIn();

private:
	TalonSRX m_hatchIntake, m_hatchActuator;
	DigitalInput m_photoeye;

	COREConstant<double> m_actuatorTopLimit;
	COREConstant<double> m_actuatorBottomLimit;
	COREConstant<double> m_hatchActuatorDeadband;
};