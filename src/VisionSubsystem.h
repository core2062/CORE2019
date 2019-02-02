
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
	double GetCargoUltraDistance();
	double GetHatchUltraDistance();
private:
	const double m_scale = (1024.0 / 2.54); 
	AnalogInput m_cargoLeftUltra, m_cargoRightUltra, m_hatchLeftUltra, m_hatchRightUltra, m_jumper;
};
