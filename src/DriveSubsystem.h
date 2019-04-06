
#pragma once

#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <COREFramework/COREScheduler.h>
#include <COREHardware/COREJoystick.h>

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

using namespace frc;

class DriveSubsystem : public CORESubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void InitTalons();
    void ToggleGear();
    void ResetEncoders(DriveSide whichSide);
    double GetDistanceInInches(DriveSide whichSide);
    void SetMotorSpeed(double speedInFraction, DriveSide);
    void SetMotorSpeed(double leftPercent, double rightPercent);
    double GetForwardPower();
    void FillCompressor();
    void LineFollower();

    COREConstant<double> driveTurnkP;
private:
    Compressor compressor;
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    TalonSRX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    DoubleSolenoid m_leftDriveShifter;
    bool m_highGear;
    COREConstant<double> m_turnPIDMultiplier, m_photoEyeLimitLeft, m_photoEyeLimitRight, m_constantForwardSpeed, 
    m_rightConstant, m_middleConstant, m_leftConstant;
    AnalogInput *IR1;
    //AnalogInput *IR2;
    AnalogInput *IR3;
    AnalogInput *IR4;
    AnalogInput *IR5;
    AnalogInput *IR6;
    AnalogInput *IR7;
    AnalogInput *IR8;
    //AnalogInput *IR9;
    AnalogInput *IR10;
    double m_rightSpeed;
	double m_leftSpeed;
};