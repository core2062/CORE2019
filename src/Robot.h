#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <DriveSubsystem.h>

/* Drive ports */
#define RIGHT_FRONT_PORT 10
#define RIGHT_BACK_PORT 11
#define LEFT_FRONT_PORT 12
#define LEFT_BACK_PORT 13
#define HATCH_INTAKE_MOTOR_PORT 14

/* Solenoids */
#define LEFT_DRIVE_SHIFTER_PCM 1
#define RIGHT_DRIVE_SHIFTER_PCM 1
#define COMPRESSOR_PCM 2
#define LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT 0
#define RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT 2 
#define LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT 1
#define RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT 3
#define HATCH_INTAKE_SOLENOID_OUT_PORT 4
#define HATCH_INTAKE_SOLENOID_IN_PORT 5


/* Sensor */
#define HATCH_INTAKE_PHOTOEYE 1

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	void robotInit() override;
    void teleopInit() override;
    void Teleop() override;
	void Test() override;
	void testInit() override;
	DriveSubsystem driveSubsystem;
};