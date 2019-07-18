#pragma once

#include <CORERobotLib.h>
#include <COREUtilities/COREConstant.h>
#include <ctre/Phoenix.h>
#include <frc/WPILib.h>

using namespace frc;

class LiftSubsystem : public CORESubsystem {
   public:
    LiftSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void SetRequestedPosition(double positionInInches);
    void SetRequestedSpeed(double speed);
    void SetFirstLevelCargoHeight();
    double GetLiftPosition();
    double GetLiftInches();
    void ResetEncoder();
    bool LiftDown();

   private:
    double m_requestedSpeed, m_requestedPosition;
    bool m_limitSwitchSetter = false;
    DigitalInput m_limitSwitch;
    COREConstant<double> m_cruiseVel, m_maxAcel;
    COREConstant<double> m_topLimit, m_bottomLimit;
    COREConstant<double> m_liftUpSpeed, m_liftDownSpeed;
    COREConstant<double> m_ticksPerInch;
    TalonSRX m_rightLiftMotor, m_leftLiftMotor;
};