#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>
Robot::Robot() : driveSubsystem() {
  
}

void Robot::Teleop() {

}

void Robot::RobotInit() {

}

void Robot::TeleopInit() {
    
}

void Robot::Test() {

}

void Robot::TestInit() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { 
	return frc::StartRobot<Robot>(); 
}
#endif
