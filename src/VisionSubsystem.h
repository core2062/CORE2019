
#pragma once
#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <Robot.h>

using namespace frc;
using namespace CORE;

class VisionSubsystem : public CORESubsystem {

public:
	VisionSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	double GetDistance();
private:
	AnalogInput m_cargoUltra, m_hatchUltra;
};
