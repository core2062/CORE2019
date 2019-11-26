#include <DriveSubsystem.h>
#include <Robot.h>
#include <frc/WPILib.h>
#include <COREFramework/COREScheduler.h>
#include <AHRS.h>

using namespace CORE;

DriveSubsystem::DriveSubsystem() : lookAhead("Waypoint follower look ahead point"),
								   driveTurnkP("Drive Turn P Value", .05),
								   m_etherAValue("Ether A Value", .6),
                                   m_etherBValue("Ether B Value", .4),
								   m_etherQuickTurnValue("Ether Quick Turn Value", 1.0),
                                   m_ticksPerInch("Drive Ticks Per Inch", (4 * 3.1415) / 1024),
								   m_leftMaster(LEFT_FRONT_PORT),
								   m_rightMaster(RIGHT_FRONT_PORT),
								   m_leftSlave(LEFT_BACK_PORT),
								   m_rightSlave(RIGHT_BACK_PORT),
                                   m_leftDriveShifter(DRIVE_SHIFTER_PCM, DRIVE_SHIFTER_HIGH_GEAR_PORT, DRIVE_SHIFTER_LOW_GEAR_PORT),
								   m_highGear(true),
								   m_turnPIDMultiplier("Turn PID Multiplier", 0.1),
								   compressor(COMPRESSOR_PCM),
								   m_pursuit(0, 0, .1, m_path, false, 0),
								   m_tracker(TankTracker::GetInstance()) {
	if (std::addressof(m_leftMaster) == nullptr) {
		std::cout << "Left master is returning a nullptr!" << endl;
	}
	if (std::addressof(m_rightMaster) == nullptr) {
		std::cout << "Right master is returning a nullptr!" << endl;
	}
	try {
        m_gyro = new AHRS(SPI::Port::kMXP);;
    } catch (std::exception ex) {
        CORELog::LogError("Error initializing gyro: " + string(ex.what()));
    }
	if (m_gyro == nullptr) {
		std::cout << "GetGyro is returning a nullptr!" << endl;
	}
	std::cout << "This is the gyro angle from drive subsystem: " << m_gyro->GetAngle() << endl;
}

DriveSubsystem::~DriveSubsystem() {
	cout << "You have reached the drive subsystem destructor"<< endl;
}
void DriveSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	driverJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_STICK_X);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_TRIGGER);
    InitTalons();
    try {
        m_gyro = new AHRS(SPI::Port::kMXP);
    } catch (std::exception ex) {
        CORELog::LogError("Error initializing gyro: " + string(ex.what()));
    }

	if (m_driveWaypointController == nullptr) {
		m_driveWaypointController = new DriveWaypointController();
	}
}

void DriveSubsystem::teleopInit() {
	// Sets ether drive values, inits talons
	COREEtherDrive::SetAB(m_etherAValue.Get(), m_etherBValue.Get());
	COREEtherDrive::SetQuickturn(m_etherQuickTurnValue.Get());
	m_driveWaypointController->Disable();
	InitTalons();
}

void DriveSubsystem::SetFrame(TankRobotFrame * frame) {
	if (m_driveWaypointController) {
		m_driveWaypointController->frame = frame;
	}
}

void DriveSubsystem::SetPos(TankPosition2d pos) {
	if(m_driveWaypointController != nullptr){
		m_driveWaypointController->ResetTracker(pos);
	}
}

void DriveSubsystem::teleop() {
	// Code for teleop. Sets motor speed based on the values for the joystick, runs compressor, 
	// toggles gears

    double mag = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
	double rot = driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);

	VelocityPair speeds = COREEtherDrive::Calculate(mag, rot, .1);
	SetMotorSpeed(speeds.left, speeds.right);
	SmartDashboard::PutNumber("Actual Gyro Yaw", GetYaw());
	SmartDashboard::PutNumber("Left side speed", speeds.left);
	SmartDashboard::PutNumber("Right side speed", speeds.right);
	SmartDashboard::PutNumber("Left side encoder", m_leftMaster.GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Right side encoder", m_rightMaster.GetSelectedSensorPosition(0));

	// if(driverJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
	// 	ToggleGear();
	// }
	//FillCompressor();

}

void DriveSubsystem::ToggleGear() {
	// Shifts from high gear to low gear or vice versa
	if (m_highGear) {
		m_leftDriveShifter.Set(DoubleSolenoid::kForward);
		m_highGear = false;
	} else {
		m_leftDriveShifter.Set(DoubleSolenoid::kReverse);
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
		m_rightSlave.Set(ControlMode::PercentOutput, speedInFraction);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT) {
		m_leftMaster.Set(ControlMode::PercentOutput, speedInFraction);
		m_leftSlave.Set(ControlMode::PercentOutput, speedInFraction);
	}
}

void DriveSubsystem::SetMotorSpeed(double leftPercent, double rightPercent) {
	// Sets speed based on percent output desired 
	SetMotorSpeed(leftPercent, DriveSide::LEFT); //Might need to reverse this for comp robot
	SetMotorSpeed(rightPercent, DriveSide::RIGHT);
}

void DriveSubsystem::InitTalons() {
	// Sets up talons
	m_leftMaster.Set(ControlMode::PercentOutput, 0);
	m_leftSlave.Set(ControlMode::PercentOutput, 0);
	m_rightMaster.Set(ControlMode::PercentOutput, 0);
	m_rightSlave.Set(ControlMode::PercentOutput, 0);

	// Encoder Functions
    m_leftMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_rightMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

    m_leftMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

	m_leftMaster.SetSensorPhase(false);
    m_rightMaster.SetSensorPhase(true);

	// Motor Inversion
	m_leftMaster.SetInverted(true);
	m_leftSlave.SetInverted(true);
	m_rightMaster.SetInverted(true);
	m_rightSlave.SetInverted(true);
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

TalonSRX * DriveSubsystem::GetLeftMaster() {
	// if (&m_leftSlave == nullptr) {
	// 	std::cout << "Left master is returning a nullptr!" << endl;
	// } else{
	// 	bool Inverted = m_leftMaster.GetInverted();
	// }
	return &m_leftMaster;
}

TalonSRX * DriveSubsystem::GetRightMaster() {
	// if (&m_rightMaster == nullptr) {
	// 	std::cout << "Right master is returning a nullptr!" << endl;
	// } else{
	// 	bool Inverted = m_rightMaster.GetInverted();
	// 	}
	return &m_rightMaster;
}

AHRS * DriveSubsystem::GetGyro() {
	try {
		if (m_gyro == nullptr) {
			std::cout << "Get Gyro is returning a null pointer" << endl;
			return nullptr;
		} else {
			return m_gyro;
		}
	}catch (std::exception ex) {
		CORELog::LogError("Error getting gyro: " + string(ex.what()));
	}
}

double DriveSubsystem::GetYaw() {
	return (double) m_gyro->GetAngle();
} 

TankRotation2d DriveSubsystem::GetGyroAngle() {
	return TankRotation2d::FromRadians(m_gyro->GetYaw());
}

void DriveSubsystem::FollowPath(TankPath * path, bool reversed, double maxAccel, double tolerance, 
	bool gradualStop) {
	m_pursuit = TankAdaptivePursuit(lookAhead.Get(), maxAccel, 0.025, path, reversed, tolerance, gradualStop);
}

bool DriveSubsystem::PathDone(TankPath * m_path) {
	if(m_driveWaypointController){
		return m_driveWaypointController->IsDone(m_path);
	}
	return true;
}

void DriveSubsystem::UpdatePathFollower() {
	TankPosition2d pos;
	
	pos = m_tracker->GetLatestFieldToVehicle();
	
	TankPosition2d::TankDelta command = m_pursuit.Update(pos, Timer::GetFPGATimestamp());

	VelocityPair setpoint = TankKinematics::InverseKinematics(command);
	double maxVel = 0.0;
	maxVel = max(maxVel, setpoint.left);
	maxVel = max(maxVel, setpoint.right);
	if (maxVel > 100){
		double scaling = 100 / maxVel;
		setpoint = VelocityPair(setpoint.left * scaling, setpoint.right * scaling);
	}
	SetMotorSpeed(setpoint.left * .01, setpoint.right * .01);
} 

std::pair<double, double> DriveSubsystem::GetEncoderInches() {
	double factor = TankKinematics::wheelDiameter.Get() * 3.14;
	return {m_leftMaster.GetSelectedSensorPosition(0) * factor, m_rightMaster.GetSelectedSensorPosition(0) * factor};
}

std::pair<double, double> DriveSubsystem::GetEncoderSpeed() {
	double factor = TankKinematics::wheelDiameter.Get() * 3.14 * 0.016666666;
	return {m_leftMaster.GetSelectedSensorVelocity(0) * factor, m_rightMaster.GetSelectedSensorVelocity(0) * factor};
}

void DriveSubsystem::ResetTracker(TankPosition2d initialPos) {
	m_tracker->Reset(Timer::GetFPGATimestamp(), initialPos);
}

void DriveSubsystem::PostLoopTask() {
	if(CORE::COREDriverstation::GetMode() == CORE::COREDriverstation::AUTON) {
		UpdatePathFollower();
	}
}
