#pragma once

#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <COREUtilities/COREConstant.h>

using namespace frc;

class LiftSubsystem : public CORESubsystem {
public:
	LiftSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void SetLift(double speed);
	void SetRequestedPosition(double position);
	void SetRequestedSpeed(double speed);
	void SetFirstLevelHatchHeight();
	void SetSecondLevelHatchHeight();
	void SetThirdLevelHatchHeight();
	void SetFirstLevelCargoHeight();
	void SetSecondLevelCargoHeight();
	void SetThirdLevelCargoHeight();
	double GetLiftPosition();
	double GetLiftInches();
	void ResetEncoder();
private:
	double heightMultiplier;
	COREConstant<double> m_firstLevelHatch, m_firstLevelCargo, m_secondLevelHatch, m_secondLevelScorer, m_thirdLevelHatch, m_thirdLevelScorer;
	TalonSRX m_rightLiftMotor, m_leftLiftMotor;
};