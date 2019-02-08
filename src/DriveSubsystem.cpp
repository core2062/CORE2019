#include <DriveSubsystem.h>
#include <Robot.h>
#include <frc/WPILib.h>
#include <COREFramework/COREScheduler.h>

using namespace CORE;

DriveSubsystem::DriveSubsystem() : lookAhead("Waypoint follower look ahead point"),
								   driveTurnkP("Drive Turn P Value", .05),
								   m_etherAValue("Ether A Value", .6),
                                   m_etherBValue("Ether B Value", .4),
								   m_etherQuickTurnValue("Ether Quick Turn Value", 1.0),
                                   m_ticksPerInch("Ticks Per Inch", (4 * 3.1415) / 1024),
								   m_leftMaster(LEFT_FRONT_PORT),
								   m_rightMaster(RIGHT_FRONT_PORT),
								   m_leftSlave(LEFT_BACK_PORT),
								   m_rightSlave(RIGHT_BACK_PORT),
                                   m_leftDriveShifter(LEFT_DRIVE_SHIFTER_PCM, LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT, LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT),
                                   m_rightDriveShifter(RIGHT_DRIVE_SHIFTER_PCM, RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT, RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT),
								   m_highGear(true),
								   m_turnPIDMultiplier("Turn PID Multiplier", 0.1),
								   compressor(COMPRESSOR_PCM),
								   m_pursuit(0, 0, 0, .1, Path(), false, 0) {
	try {
        	m_gyro = new AHRS(SPI::Port::kMXP);
    } catch (std::exception ex) {
        CORELog::LogError("Error initializing gyro: " + string(ex.what()));
    }
}

void DriveSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	driverJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_STICK_Y);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_TRIGGER);
    InitTalons();
}

void DriveSubsystem::teleopInit() {
	// Sets ether drive values, inits talons
	COREEtherDrive::SetAB(m_etherAValue.Get(), m_etherBValue.Get());
	COREEtherDrive::SetQuickturn(m_etherQuickTurnValue.Get());
	InitTalons();
}


void DriveSubsystem::teleop() {
	// Code for teleop. Sets motor speed based on the values for the joystick, runs compressor, 
	// toggles gears
	if(driverJoystick != nullptr) {
    	double left = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
		double right = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
		SetMotorSpeed(left, right);
		if(driverJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
			ToggleGear();
		}
		FillCompressor();
	} else {
		SetMotorSpeed(0, 0);
	}

}

void DriveSubsystem::ToggleGear() {
	// Shifts from high gear to low gear or vice versa
	if (m_highGear) {
		m_leftDriveShifter.Set(DoubleSolenoid::kForward);
		m_rightDriveShifter.Set(DoubleSolenoid::kForward);
		m_highGear = false;
	} else {
		m_leftDriveShifter.Set(DoubleSolenoid::kReverse);
		m_rightDriveShifter.Set(DoubleSolenoid::kReverse);
		m_highGear = true;
	}
}

void DriveSubsystem::ResetEncoders(DriveSide whichSide){
	// Resets encoders
	// Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_rightMaster.GetSensorCollection().SetQuadraturePosition(0, 10);
		m_rightMaster.SetSelectedSensorPosition(0, 0, 10);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_leftMaster.GetSensorCollection().SetQuadraturePosition(0, 10);
		m_leftMaster.SetSelectedSensorPosition(0, 0, 10);
	}
}

double DriveSubsystem::GetDistanceInInches(DriveSide whichSide) {
	// Returns inches traveled based on the sensor position
	double accumulator = 0;
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT) {
		accumulator += abs(m_rightMaster.GetSelectedSensorPosition(0));
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT) {
		accumulator += abs(m_leftMaster.GetSelectedSensorPosition(0));
	}
	if (whichSide == DriveSide::BOTH){
		accumulator *= 0.5;
	}
	return accumulator / m_ticksPerInch.Get();
}

void DriveSubsystem::SetMotorSpeed(double speedInFraction, DriveSide whichSide) {
	// Sets motor speed based on drive side and desired speed
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT) {
		m_rightMaster.Set(ControlMode::PercentOutput, speedInFraction);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT) {
		m_leftMaster.Set(ControlMode::PercentOutput, speedInFraction);
	}
}

void DriveSubsystem::SetMotorSpeed(double leftPercent, double rightPercent) {
	// Sets speed based on percent output desired 
	SetMotorSpeed(leftPercent, DriveSide::LEFT);
	SetMotorSpeed(rightPercent, DriveSide::RIGHT);
}

void DriveSubsystem::InitTalons() {
	// Sets up talons
    m_leftMaster.Set(ControlMode::Follower, LEFT_BACK_PORT);
    m_rightMaster.Set(ControlMode::Follower, RIGHT_BACK_PORT);

	m_leftMaster.Set(ControlMode::PercentOutput, 0);
	m_rightMaster.Set(ControlMode::PercentOutput, 0);

    m_leftMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_rightMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

    m_leftMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

	m_leftMaster.SetSensorPhase(false);
    m_rightMaster.SetSensorPhase(true);

	m_leftMaster.SetInverted(false);
	m_rightMaster.SetInverted(true);
}

double DriveSubsystem::GetForwardPower() {
	// Returns current power being exerted
	double left = m_leftMaster.GetSelectedSensorPosition(0);
	double right = m_rightMaster.GetSelectedSensorPosition(0);
	double power  = 0;
	if(left > 0 || right > 0) {
		power = left + right;
		power*=.25;
		power = (power < 0)?0:power;
	}
	return power;
}

void DriveSubsystem::FillCompressor() {
	// Code to run the compressor. Maybe should be moved to Robot?
	if (compressor.GetPressureSwitchValue()) {
		compressor.SetClosedLoopControl(false);
	} else {
		compressor.SetClosedLoopControl(true);
	}
}

Rotation2d DriveSubsystem::GetGyroAngle() {
	return Rotation2d::FromRadians(m_gyro->GetYaw());
}

void DriveSubsystem::SetPosition(Position2d pos) {
	
}

void DriveSubsystem::FollowPath(Path path, bool reversed, double maxAccel, double tolerance, 
	bool gradualStop) {
	m_pursuit = AdaptivePursuit(lookAhead.Get(), driveTurnkP.Get(), maxAccel, 0.025, path, reversed, tolerance, 
		gradualStop);
}

bool DriveSubsystem::PathDone() {
	return m_pursuit.IsDone();
}

void DriveSubsystem::PreLoopTask() {
	RunTracker();
	if(CORE::COREDriverstation::GetMode() == CORE::COREDriverstation::AUTON) {

	}
}

void DriveSubsystem::RunTracker() {
	
}

void DriveSubsystem::ResetTracker() {

}

// void DriveWaypointController::UpdatePathFollower() {
// 	Position2d pos;
// 	if(frame == nullptr){
// 		pos = m_tracker->getLatestFieldToVehicle();
// 	} else {
// 		pos = frame->getLatest();

// 	Position2d::Delta command = m_pursuit.update(pos, Timer::GetFPGATimestamp());

// 	VelocityPair setpoint = TankKinematics::inverseKinematics(command);
// 	double maxVel = 0.0;
// 	maxVel = max(maxVel, setpoint.left);
// 	maxVel = max(maxVel, setpoint.right);
// 	if (maxVel > 100){
// 		double scaling = 100 / maxVel;
// 		setpoint = VelocityPair(setpoint.left * scaling, setpoint.right * scaling);
// 	}
// 	Robot->driveSubsystem.setMotorSpeed(setpoint.left * .01, setpoint.right * .01);
// }