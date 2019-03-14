#include "DriveGyroController.h"
#include "COREUtilities/COREDriverstation.h"
#include "Robot.h"

DriveGyroController::DriveGyroController(double target, double tolerance, bool relative) {
	if(relative) {
		m_target = Robot::GetInstance()->driveSubsystem.GetGyroAngle().RotateBy(TankRotation2d::FromDegrees(target));
	} else {
		m_target = TankRotation2d::FromDegrees(target);
	}
	m_tolerance = tolerance;
	m_error = 999999;
}

void DriveGyroController::Init(double target, double tolerance, bool relative) {
	if(relative){
		m_target = Robot::GetInstance()->driveSubsystem.GetGyroAngle().RotateBy(TankRotation2d::FromDegrees(target));
	} else {
		m_target = TankRotation2d::FromDegrees(target);
	}
	m_tolerance = tolerance;
	m_error = GetError();
}

void DriveGyroController::PostLoopTask() {
	if(COREDriverstation::IsEnabled() && (COREDriverstation::GetMode() == COREDriverstation::gameMode::AUTON)){
		EnabledLoop();
	}
}

void DriveGyroController::EnabledLoop() {
	m_error = GetError();

	double output = m_error * Robot::GetInstance()->driveSubsystem.driveTurnkP.Get();
	Robot::GetInstance()->driveSubsystem.SetMotorSpeed(output, -output);
}

bool DriveGyroController::IsDone() {
	return (abs(m_error) < m_tolerance);
}

double DriveGyroController::GetError() {
	double errorA =  m_target.GetDegrees() - Robot::GetInstance()->driveSubsystem.GetGyroAngle().GetDegrees();
	double errorB =  m_target.Opposite().GetDegrees() - Robot::GetInstance()->driveSubsystem.GetGyroAngle().Opposite().GetDegrees();
	double bestError;
	if(errorA <= errorB){
		bestError = errorA;
	} else {
		bestError = errorB;
	}
	return bestError;
}
