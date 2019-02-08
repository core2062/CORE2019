
#pragma once

#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <COREFramework/COREScheduler.h>
#include <COREHardware/COREJoystick.h>
#include <WaypointFollower/WaypointFollower.h>
#include <AHRS.h>

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

using namespace frc;

class DriveSubsystem : public CORESubsystem, public CORETask {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void PreLoopTask() override;
    void InitTalons();
    void ToggleGear();

    void ResetEncoders(DriveSide whichSide);
    double GetDistanceInInches(DriveSide whichSide);
    void SetMotorSpeed(double speedInFraction, DriveSide);
    void SetMotorSpeed(double leftPercent, double rightPercent);
    double GetForwardPower();
    void FillCompressor();

    // Autonomous functions
    Rotation2d GetGyroAngle();
    void SetPosition(Position2d pos);
    void FollowPath(Path path, bool reversed = false, double maxAccel = 25.0, 
        double tolerance = 0.25, bool gradualStop = true);
    AdaptivePursuit m_pursuit;
        bool PathDone();
    void RunTracker(); 
    void ResetTracker();

    AHRS * m_gyro;

    COREConstant<double> driveTurnkP, lookAhead;
private:
    Compressor compressor;
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    TalonSRX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
    COREConstant<double> m_turnPIDMultiplier;
};