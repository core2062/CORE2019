
#pragma once

#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <COREFramework/COREScheduler.h>
#include <COREHardware/COREJoystick.h>
#include <WaypointFollower/tank/TankWaypointFollower.h>
#include <AHRS.h>

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

using namespace frc;

class DriveSubsystem : public CORESubsystem, public CORETask {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void PostLoopTask() override;
    void InitTalons();
    void ToggleGear();
    void ResetEncoders(DriveSide whichSide);
    double GetDistanceInInches(DriveSide whichSide);
    void SetMotorSpeed(double speedInFraction, DriveSide);
    void SetMotorSpeed(double leftPercent, double rightPercent);
    double GetForwardPower();
    void FillCompressor();
    TalonSRX * GetRightMaster();
    TalonSRX * GetLeftMaster();
    AHRS * GetGyro();
    TankRotation2d GetGyroAngle();
    double GetYaw();

    void FollowPath(TankPath path, bool reversed, double maxAccel, double tolerance, bool gradualStop);
    TankAdaptivePursuit m_pursuit;
    bool PathDone();
    void ResetTracker(TankPosition2d initialPos);
    void UpdatePathFollower();
    std::pair<double, double> GetEncoderInches();
    std::pair<double, double> GetEncoderSpeed();
    void HardResetYaw();
    void SoftResetYaw();
    TalonSRX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    AHRS * m_gyro;
    COREConstant<double> driveTurnkP, lookAhead;
private:
    TankPath m_path;
    TankTracker * m_tracker;
    Compressor compressor;
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    DoubleSolenoid m_leftDriveShifter;
    bool m_highGear;
    COREConstant<double> m_turnPIDMultiplier;

};