#include "DriveWaypointController.h"
#include "Robot.h"

DriveWaypointController::DriveWaypointController():
	m_path(),
    m_tracker(TankTracker::GetInstance()),
	m_pursuit(0,0,.1,m_path,false,0) {
		

}

void DriveWaypointController::PreLoopTask() {
	TankTracker::GetInstance()->Loop();
}

void DriveWaypointController::PostLoopTask() {
	if (m_enabled && (COREDriverstation::IsAutonomous())){
		EnabledLoop();
	}
}

void DriveWaypointController::EnabledLoop(){
	UpdatePathFollower();
}

void DriveWaypointController::Enable() {
	m_enabled = true;
}

void DriveWaypointController::Disable() {
	m_enabled = false;
}

void DriveWaypointController::StartPath(TankPath * path, bool reversed,
		double maxAccel, double tolerance, bool gradualStop, double lookahead) {
	m_pursuit = TankAdaptivePursuit(lookahead, maxAccel, .025, path, reversed, tolerance, gradualStop);
}

void DriveWaypointController::ResetTracker(TankPosition2d initialPos) {
	m_tracker->Reset(Timer::GetFPGATimestamp(), initialPos);
}

bool DriveWaypointController::IsDone(TankPath * m_path) {
	return m_pursuit.IsDone(m_path);
}

bool DriveWaypointController::CheckEvent(std::string event) {
	return m_pursuit.CheckEvent(event);
}

void DriveWaypointController::UpdatePathFollower() {
	TankPosition2d pos;
	if(frame == nullptr){
		pos = m_tracker->GetLatestFieldToVehicle();
	} else {
		pos = frame->GetLatest();
	}
	TankPosition2d::TankDelta command = m_pursuit.Update(pos, Timer::GetFPGATimestamp());
	VelocityPair setpoint = TankKinematics::InverseKinematics(command);
	double maxVel = 0.0;
	maxVel = max(maxVel, setpoint.left);
	maxVel = max(maxVel, setpoint.right);
	if (maxVel > 100){
		double scaling = 100 / maxVel;
		setpoint = VelocityPair(setpoint.left * scaling, setpoint.right * scaling);
	}
	Robot::GetInstance()->driveSubsystem.SetMotorSpeed(setpoint.left * .01, setpoint.right * .01);
}

void DriveWaypointController::AutonInitTask(){
	cout<<"Waypoint Controller Init Start"<<endl;
	TalonSRX* Left = Robot::GetInstance()->driveSubsystem.GetLeftMaster();
	TalonSRX* Right = Robot::GetInstance()->driveSubsystem.GetRightMaster();
	AHRS* Gyro = Robot::GetInstance()->driveSubsystem.GetGyro();
	if (Left == nullptr) {
		cout<<"Left is a null ptr" <<endl;
	} 
	if (Right == nullptr) {
		cout<<"Right is a null ptr" <<endl;
	} 
   	TankTracker::GetInstance()->Init(Left, Right, Gyro);
   	std::cout << "Waypoint Controller Init End" << std::endl;
}
