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

}

void Robot::teleopInit() {
    
}

void Robot::test() {

}

void Robot::testInit() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { 
	return frc::StartRobot<Robot>(); 
}
#endif
