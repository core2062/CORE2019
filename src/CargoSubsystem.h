#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>

using namespace CORE;

class CargoSubsystem : public CORESubsystem {
public:
	CargoSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void SetIntake();
	bool IsIntaking();
	void SetOuttake();
	
private:
	TalonSRX m_rightSideIntake, m_leftSideIntake;
	frc::DigitalInput m_cargoLimitSwitch; 
};