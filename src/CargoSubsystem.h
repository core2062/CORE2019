#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;

class CargoSubsystem : public CORESubsystem {
public:
	CargoSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void setIntake();
	bool isIntaking();
	void setOuttake();
	
	TalonSRX m_rightSideIntake, leftSideIntake;
private:
	DigitalInput m_cargoLimitSwitch
};