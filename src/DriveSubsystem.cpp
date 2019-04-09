#include <DriveSubsystem.h>
#include <Robot.h>
#include <frc/WPILib.h>
#include <COREFramework/COREScheduler.h>

using namespace CORE;


DriveSubsystem::DriveSubsystem() : driveTurnkP("Drive Turn P Value", .05),
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
								   m_photoEyeLimitLeft("Photoeye Cutoff Limit (left)"),
								   m_photoEyeLimitRight("Photoeye Cutoff Limit (right)"),
								   m_constantForwardSpeed("Constant Forward Speed"),
								   m_rightConstant("Right Line Follower Speed"),
								   m_middleConstant("Middle Line Follower Speed"),
								   m_leftConstant("Left Line Follower Speed"),
								   compressor(COMPRESSOR_PCM) {
									   IR1 = new AnalogInput(0);
									   //IR2 = new AnalogInput(1);
									   IR3 = new AnalogInput(1);
									   IR4 = new AnalogInput(2);
									   IR5 = new AnalogInput(3);
									   IR6 = new AnalogInput(4);
									   IR7 = new AnalogInput(5);
									   IR8 = new AnalogInput(6);
									   //IR9 = new AnalogInput(3);
									   IR10 = new AnalogInput(7);
}

void DriveSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	driverJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_STICK_X);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_TRIGGER);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_BUTTON);
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
    double mag = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double rot = driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);

	VelocityPair speeds = COREEtherDrive::Calculate(mag, rot, .1);
	SmartDashboard::PutNumber("Left side speed", speeds.left);
	SmartDashboard::PutNumber("Right side speed", speeds.right);
	SmartDashboard::PutNumber("Left side encoder", m_leftSlave.GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Right side encoder", m_rightMaster.GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Direction of Line Follower", m_rightSpeed - m_leftSpeed);


	SmartDashboard::PutNumber("IR1", IR1->GetValue());
	//SmartDashboard::PutNumber("IR2", IR2->GetValue());
	SmartDashboard::PutNumber("IR3", IR3->GetValue());
	SmartDashboard::PutNumber("IR4", IR4->GetValue());
	SmartDashboard::PutNumber("IR5", IR5->GetValue());
	SmartDashboard::PutNumber("IR6", IR6->GetValue());
	SmartDashboard::PutNumber("IR7", IR7->GetValue());
	SmartDashboard::PutNumber("IR8", IR8->GetValue());
	//SmartDashboard::PutNumber("IR9", IR9->GetValue());
	SmartDashboard::PutNumber("IR10", IR10->GetValue());
	
	SmartDashboard::PutBoolean("IR1B", IR1->GetValue() >= m_photoEyeThresholdLeft.Get());
	//SmartDashboard::PutBoolean("IR2B", IR2->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR3B", IR3->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR4B", IR4->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR5B", IR5->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR6B", IR6->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR7B", IR7->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR8B", IR8->GetValue() >= m_photoEyeThresholdLeft.Get());
	//SmartDashboard::PutBoolean("IR9B", IR9->GetValue() >= m_photoEyeThresholdLeft.Get());
	SmartDashboard::PutBoolean("IR10B", IR10->GetValue() >= m_photoEyeThresholdLeft.Get());
	
	SmartDashboard::PutNumber("Right Line Follower Speed", m_rightSpeed);
	SmartDashboard::PutNumber("Left Line Follower Speed", m_leftSpeed);

	if(driverJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
		ToggleGear();
	}
	FillCompressor();

	if(driverJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) && m_highGear) {
		ToggleGear();
	}
	if(driverJoystick->GetFallingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) && !m_highGear) {
		ToggleGear();
		m_leftSpeed = 0;
		m_rightSpeed = 0;
	}
	if(driverJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
		LineFollower();
	} else {
		SetMotorSpeed(speeds.left, speeds.right);
	}


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
		m_leftSlave.GetSensorCollection().SetQuadraturePosition(0, 10);
		m_leftSlave.SetSelectedSensorPosition(0, 0, 10);
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
    m_leftSlave.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_rightMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

    m_leftSlave.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_rightMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

	m_leftSlave.SetSensorPhase(false);
    m_rightMaster.SetSensorPhase(true);

	// Motor Inversion
	m_leftMaster.SetInverted(false);
	m_leftSlave.SetInverted(false);
	m_rightMaster.SetInverted(true);
	m_rightSlave.SetInverted(true);
}

double DriveSubsystem::GetForwardPower() {
	// Returns current power being exerted
	double left = m_leftSlave.GetSelectedSensorPosition(0);
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

void DriveSubsystem::LineFollower() {
	m_leftSpeed = 0;
	m_rightSpeed = 0;
	
	if(IR1->GetValue() >= m_photoEyeLimitLeft.Get()) {
		// += (1 * m_leftConstant.Get());
		m_leftSpeed += 4;
	}

	if(IR3->GetValue() >= m_photoEyeLimitLeft.Get()) {
		// if(IR1->GetValue() >= m_photoEyeLimitLeft.Get()) {
		// 	m_leftSpeed += (-0.6 * m_leftConstant.Get());
		// } else {
		// 	m_leftSpeed += (0.4 * m_leftConstant.Get());
		// }
		m_leftSpeed += 3;
	}

	if(IR4->GetValue() >= m_photoEyeLimitLeft.Get()) {
		// if(IR1->GetValue() >= m_photoEyeLimitLeft.Get() && IR3->GetValue() >= m_photoEyeLimitLeft.Get()) {
		// 	m_leftSpeed += (-0.2 * m_leftConstant.Get());	
		// } else if(IR3->GetValue() >= m_photoEyeLimitLeft.Get()){
		// 	m_leftSpeed += (-0.2 * m_leftConstant.Get());
		// } else {

		// }
		m_leftSpeed += 2;
	}

	if(IR5->GetValue() >= m_photoEyeLimitLeft.Get()) {	
		// m_rightSpeed += (1 * m_middleConstant.Get());
		// m_leftSpeed += (1 * m_middleConstant.Get());
		m_leftSpeed += 1;
	}
	
	if(IR6->GetValue() >= m_photoEyeLimitRight.Get()) {
		// m_rightSpeed += (1 * m_middleConstant.Get());
		// m_leftSpeed += (1 * m_middleConstant.Get());
		m_leftSpeed += -1;
	}
	
	if(IR7->GetValue() >= m_photoEyeLimitRight.Get()) {
		// if(IR8->GetValue() >= m_photoEyeLimitRight.Get() && IR10->GetValue() >= m_photoEyeLimitRight.Get()) {
		// 	m_rightSpeed -= (0.15 * m_rightConstant.Get())			
		// } else {
		// 	m_rightSpeed += (0 * m_rightConstant.Get());
		// }
		m_leftSpeed += -2;
	}
	
	if(IR8->GetValue() >= m_photoEyeLimitRight.Get()) {
		// if(IR10->GetValue() >= m_photoEyeLimitRight.Get()){
		// 	m_rightSpeed -= (0.25 * m_rightConstant.Get())
		// } else {
		// 	m_rightSpeed += (0.44 * m_rightConstant.Get());
		// }
		m_leftSpeed += -3;
	}
	
	if(IR10->GetValue() >= m_photoEyeLimitRight.Get()) {
		// m_rightSpeed += (0.56 * m_rightConstant.Get());
		m_leftSpeed += -4;	
	}

	// m_leftSpeed += m_constantForwardSpeed.Get();
	// m_rightSpeed += m_constantForwardSpeed.Get();
	SetMotorSpeed(-(m_leftSpeed/12.0) + m_constantForwardSpeed.Get(), m_leftSpeed/12.0 + m_constantForwardSpeed.Get());
	//SetMotorSpeed(m_leftSpeed, m_rightSpeed);
}