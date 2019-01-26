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
	void ToggleHatchIntake();
	void SetIntakeOff();
	bool GetHatchState();
	bool isDown;

	frc::DigitalInput m_photoeye;
	TalonSRX m_hatchIntake;


private:
	frc::DoubleSolenoid m_hatchIntakeSolenoid;
};