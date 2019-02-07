#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <frc/WPILib.h>


using namespace CORE;

class HatchIntakeSubsystem : public CORESubsystem {
public:
	HatchIntakeSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void SetIntakeOn();
	void SetIntakeOff();
	void HatchActuatorUp();
	void HatchActuatorDown();

private:
	TalonSRX m_hatchIntake, m_hatchActuator;
	frc::DigitalInput m_photoeye;

	COREConstant<double> m_actuatorTopLimit, m_actautorBottomLimit;
};