#pragma once
#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include "WaypointFollower/tank/TankRobotFrame.h"

//#define OLD_MATH

using namespace CORE;

class VisionSubsystem : public CORESubsystem, public CORETask {
public:

    VisionSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void AutonInitTask() override;
    void PreLoopTask() override;
    TankRotation2d GetError();
    double GetErrorPercent();
    TankPath * GetPath();
    TankRobotFrame * GetFrame();
    void CalculatePath();
    double GetRocketX();

    double GetUltraDist();

    COREConstant<double> rocketPlaceDist;
    COREConstant<double> ultrakP;
    shared_ptr<NetworkTable> visionTable;
private:
    const string frontCamera = "front";
    const string backCamera = "back";
    string whichCamera = frontCamera;
    std::vector<double> m_timeOffsets;
    double m_timeOffset = 0.0;
    double m_lastPiTime = 0.0;
    double m_rocketX = 0.0;

    TankRotation2d m_targetRotation;

    COREConstant<double> m_imageWidth;
    COREConstant<double> m_horizontalFieldOfView;
    COREConstant<double> m_rocketApproachDist;
    COREConstant<double> m_ultraToCenterDist;
    COREConstant<int> m_rocketApproachSamples;

    TankRobotFrame m_visionFrame;
    TankPath m_pathToRocket;

    frc::AnalogInput m_leftUltra;
    frc::AnalogInput m_rightUltra;
    frc::AnalogInput m_jumper;
};