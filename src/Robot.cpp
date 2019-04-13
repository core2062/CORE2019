#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>
Robot * Robot::m_instance;

Robot::Robot() {
	m_instance = this;
	std::cout<<"Robot Constructor"<<endl;
}

void Robot::teleop() {

}

void Robot::robotInit() {
	//COREScheduler::AddAuton(&controlledAutonomous);
}

void Robot::teleopInit() {
    
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
