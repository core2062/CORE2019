#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <DriveSubsystem.h>
#include <CargoSubsystem.h>
#include <LiftSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>

using namespace CORE;
using namespace std;

class Auton : public COREAuton {
    Auton();
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    
    DriveSubsystem driveSubsystem;
	CargoSubsystem cargoSubsystem;
	//HatchIntakeSubsystem hatchSubsystem;
	HatchScorerSubsystem hatchScorerSubsystem;
	LiftSubsystem liftSubsystem;
}