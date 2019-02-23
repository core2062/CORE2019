#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <DriveSubsystem.h>
#include <SuperStructure.h>
#include <CargoSubsystem.h>
#include <LiftSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>


/* Drive Motor Ports */
//Right Front Drive Motor
#define RIGHT_FRONT_PORT 20
//Right Back Drive Motor
#define RIGHT_BACK_PORT 1
//Left Front Drive Motor
#define LEFT_FRONT_PORT 19
//Left Back Drive Motor
#define LEFT_BACK_PORT 32

//Left Cargo Intake
#define LEFT_INTAKE_PORT 22
//Right Cargo Intake
#define RIGHT_INTAKE_PORT 23
//Left Lift Motor
#define LEFT_LIFT_PORT 31
//Right Lift Motor
#define RIGHT_LIFT_PORT 30
//Hatch Intake Motor
#define HATCH_INTAKE_PORT 21

/* Solenoids */
// Drive 
#define DRIVE_SHIFTER_PCM 0
#define COMPRESSOR_PCM 0

#define DRIVE_SHIFTER_HIGH_GEAR_PORT 6
#define DRIVE_SHIFTER_LOW_GEAR_PORT 7



//Hatch Scorer
//Claw
#define HATCH_SCORER_CLAW_IN 0
#define HATCH_SCORER_CLAW_OUT 1
//Punch
#define HATCH_SCORER_PUNCH_IN 2
#define HATCH_SCORER_PUNCH_OUT 3
/*
Solenoids
Hatch Scorer
2, 3 = In, Out
0, 1 = Up, Down
*/

/* Sensor */
#define HATCH_INTAKE_PHOTOEYE 1
#define LIFT_LIMIT_SWITCH_PORT 19
#define CARGO_LIMIT_SWITCH_PORT 9

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
	static Robot * GetInstance();

	DriveSubsystem driveSubsystem;
	CargoSubsystem cargoSubsystem;
	HatchIntakeSubsystem hatchIntakeSubsystem;
	HatchScorerSubsystem hatchScorerSubsystem;
	LiftSubsystem liftSubsystem;
	SuperStructure superStructure;

private:
	static Robot * m_instance;
};
