#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>
Robot::Robot() : driveSubsystem() {
  
}

void Robot::Teleop() {
    double left = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double right = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);

	driveSubsystem.SetMotorSpeed(left, right);
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
