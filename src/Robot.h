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
#define LEFT_INTAKE_PORT 14
#define RIGHT_INTAKE_PORT 15
#define DIGITAL_INPUT_PORT 16

/* Solenoids */
#define LEFT_DRIVE_SHIFTER_PCM 1
#define RIGHT_DRIVE_SHIFTER_PCM 1
#define COMPRESSOR_PCM 2
#define LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT 0
#define RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT 2 
#define LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT 1
#define RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT 3

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
	DriveSubsystem driveSubsystem;
};