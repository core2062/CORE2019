#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>
Robot * Robot::m_instance;

Robot::Robot() {
	m_instance = this;

}

void Robot::teleop() {

}

void Robot::robotInit() {
	CORE::COREScheduler::AddAuton(&controlledAutonomous);
	CORE::COREScheduler::AddSubsystem(&driveSubsystem);
	CORE::COREScheduler::AddSubsystem(&cargoSubsystem);
	CORE::COREScheduler::AddSubsystem(&hatchScorerSubsystem);
	CORE::COREScheduler::AddSubsystem(&liftSubsystem);
}

void Robot::teleopInit() {
    cout<<"Robot Subsystem Init"<< endl;
}

void Robot::test() {

}

void Robot::testInit() {
  
}

Robot * Robot::GetInstance() {
	return m_instance;
}

#ifndef RUNNING_FRC_TESTS
int main() { 
	return frc::StartRobot<Robot>(); 
}
#endif
