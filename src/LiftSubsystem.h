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
	void SetRequestedPosition(double positionInInches);
	void SetRequestedSpeed(double speed);

	void SetFirstLevelHatchHeight();
	void SetSecondLevelHatchHeight();
	void SetThirdLevelHatchHeight();
	void SetFirstLevelCargoHeight();
	void SetSecondLevelCargoHeight();
	void SetThirdLevelCargoHeight();

	bool IsFirstLevelCargo();
	bool IsFirstLevelHatch();
	bool IsSecondLevelCargo();
	bool IsSecondLevelHatch();
	bool IsThirdLevelCargo();
	bool IsThirdLevelHatch();

	double GetLiftPosition();
	double GetLiftInches();
	void ResetEncoder();
	bool LiftDown();
private:
	double m_requestedSpeed, m_requestedPosition;
	DigitalInput m_limitSwitch;
	COREConstant<double> m_cruiseVel, m_maxAcel;
	COREConstant<double> m_topLimit, m_bottomLimit;
	COREConstant<double> m_liftUpSpeed, m_liftDownSpeed;
	COREConstant<double> m_firstLevelHatch, m_firstLevelCargo, m_secondLevelHatch, 
		m_secondLevelCargo, m_thirdLevelHatch, m_thirdLevelCargo, m_ticksPerInch;
	TalonSRX m_rightLiftMotor, m_leftLiftMotor;
};