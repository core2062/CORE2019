#include <CORERobotLib.h>
#include <LiftSubsystem.h>
#include <Robot.h>
#include <frc/WPILib.h>

using namespace CORE;
// Fill in with limit switch port and actual lift ports
LiftSubsystem::LiftSubsystem() : m_ticksPerInch("Lift Ticks per inch", 368.667),
                                 m_bottomLimit("Lift bottom limit"),
                                 m_topLimit("Lift top limit"),
                                 m_cruiseVel("Lift cruise velocity"),
                                 m_maxAcel("Max lift acceleration"),
                                 m_liftUpSpeed("Lift Up Speed"),
                                 m_liftDownSpeed("Lift Down Speed"),
                                 m_limitSwitch(8),
                                 m_rightLiftMotor(RIGHT_LIFT_PORT),
                                 m_leftLiftMotor(LEFT_LIFT_PORT) {
}

// Configuration for robot turn on
void LiftSubsystem::robotInit() {
    m_leftLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_leftLiftMotor.SetInverted(true);
    //m_leftLiftMotor.Follow(m_rightLiftMotor);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);

    m_leftLiftMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_leftLiftMotor.SetSelectedSensorPosition(0, 0, 0);
    m_leftLiftMotor.SetSensorPhase(true);
    cout << "Lift Subsystem Init" << endl;
}

// Configuration for teleop
void LiftSubsystem::teleopInit() {
    //SetRequestedPosition(GetLiftInches());
    m_rightLiftMotor.ConfigMotionCruiseVelocity(m_cruiseVel.Get(), 0);
    m_rightLiftMotor.ConfigMotionAcceleration(m_maxAcel.Get(), 0);
    //SetRequestedPosition(0);
    cout << "Lift Subsystem Teleop Init" << endl;
}

void LiftSubsystem::teleop() {
    double liftPosition = GetLiftInches();
    // Data for reference on SmartDashboard
    SmartDashboard::PutNumber("Lift requested position", m_requestedPosition);
    SmartDashboard::PutNumber("Lift position in inches", liftPosition);
    SmartDashboard::PutNumber("Lift position in ticks", m_leftLiftMotor.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("Limit Switch", m_limitSwitch.Get());
    // Check to see which way the lift would run if this value is positive
    // Make sure that the lift is giving very little power when it is first being tested

    // Sets the requested speed to the value from the joystick
    SetRequestedSpeed(-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y));

    // Stops the motors if we are at the top or bottom position, and resets encoders at the bottom of the lift
    if (m_requestedSpeed > 0 && liftPosition > m_topLimit.Get()) {
        m_requestedSpeed = 0;
        SetRequestedPosition(m_topLimit.Get());
    } else if (LiftDown()) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed = 0;
            SetRequestedPosition(0);
        }
        ResetEncoder();
    }

    // Checks requested speed and either sets motors based on motion magic or percent output based on magnitude
    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.01) {
        m_rightLiftMotor.Set(ControlMode::PercentOutput, m_requestedSpeed);
        m_leftLiftMotor.Set(ControlMode::PercentOutput, m_requestedSpeed);
        SetRequestedPosition(liftPosition);
    } else {
        m_rightLiftMotor.Set(ControlMode::MotionMagic, m_requestedPosition);
        m_leftLiftMotor.Set(ControlMode::MotionMagic, m_requestedPosition);
        // m_rightLiftMotor.Set(ControlMode::PercentOutput, 0);
        // m_leftLiftMotor.Set(ControlMode::PercentOutput, 0);
    }
}

// Sets the requested position and modifies if the desired position is below the minimum
// or above the maximum
void LiftSubsystem::SetRequestedPosition(double positionInInches) {
    auto position = (int)(positionInInches * m_ticksPerInch.Get());
    position = max(position, 0);
    position = min(position, (int)(m_topLimit.Get() * m_ticksPerInch.Get()));
    m_requestedPosition = position;
}
// Sets the speed to the desired speed
// Scales the requested speed down to make sure the lift does not move too quickly
void LiftSubsystem::SetRequestedSpeed(double speed) {
    m_requestedSpeed = speed;
    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.01) {
        if (m_requestedSpeed < 0) {
            //Scales speed when going down
            m_requestedSpeed *= m_liftDownSpeed.Get();
        } else {
            //Scales speed when going up
            m_requestedSpeed *= m_liftUpSpeed.Get();
        }
    } else {
        m_requestedSpeed = 0;
    }
}

// Returns the current position in ticks

double LiftSubsystem::GetLiftPosition() {
    return m_leftLiftMotor.GetSelectedSensorPosition(0);
}

// Returns the current position in inches

double LiftSubsystem::GetLiftInches() {
    return GetLiftPosition() / m_ticksPerInch.Get();
}

// Returns whether the lift is at the bottom or not

bool LiftSubsystem::LiftDown() {
    return !m_limitSwitch.Get();
}

// Resets lift encoders

void LiftSubsystem::ResetEncoder() {
    m_leftLiftMotor.SetSelectedSensorPosition(0, 0, 0);
}
