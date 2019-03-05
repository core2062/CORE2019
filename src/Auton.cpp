#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>

Auton::Auton() : COREAuton("Sam Drive") {

}

void Auton::AutonomousInit() {
    driveSubsystem->teleopInit();
    cargoSubsystem->teleopInit();
    hatchScorerSubsystem->teleopInit();
    liftSubsystem->teleopInit();
}

void Auton::AutonomousPeriodic() {
    driveSubsystem->teleop();
    cargoSubsystem->teleop();
    hatchScorerSubsystem->teleop();
    liftSubsystem->teleop();
}