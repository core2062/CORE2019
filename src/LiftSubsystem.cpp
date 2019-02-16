#include <LiftSubsystem.h>
#include <frc/WPILib.h>
#include <Robot.h>
#include <CORERobotLib.h>

using namespace CORE;
// Fill in with limit switch port and actual lift ports
LiftSubsystem::LiftSubsystem() : m_firstLevelHatch("First Level Hatch Height"),
                                 m_firstLevelCargo("First Level Cargo Height"),
                                 m_secondLevelHatch("Second Level Hatch Height"),
                                 m_secondLevelCargo("Second Level Cargo Height"),
                                 m_thirdLevelHatch("Third Level Hatch Height"),
                                 m_thirdLevelCargo("Third Level Cargo Height"),
                                 m_ticksPerInch("Ticks per inch"),
                                 m_bottomLimit("Lift bottom limit"),
                                 m_topLimit("Lift top limit"),
                                 m_cruiseVel("Lift cruise velocity"),
                                 m_maxAcel("Max lift acceleration"),
                                 m_limitSwitch(0),
                                 m_rightLiftMotor(16),
                                 m_leftLiftMotor(17) {

}

// Configuration for robot turn on 
void LiftSubsystem::robotInit(){
    m_leftLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_leftLiftMotor.Follow(m_rightLiftMotor);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

// Configuration for teleop
void LiftSubsystem::teleopInit(){
    SetRequestedPosition(GetLiftInches());
    m_rightLiftMotor.ConfigMotionCruiseVelocity(m_cruiseVel.Get(), 0);
    m_rightLiftMotor.ConfigMotionAcceleration(m_maxAcel.Get(), 0);
}

void LiftSubsystem::teleop() {
    // Data for reference on SmartDashboard
    SmartDashboard::PutNumber("Lift requested position", m_requestedPosition);
    SmartDashboard::PutNumber("Lift position in inches", m_rightLiftMotor.GetSelectedSensorPosition(0)
        m_ticksPerInch.Get());
    SmartDashboard::PutNumber("Lift position in ticks", m_rightLiftMotor.GetSelectedSensorPosition(0));
    // Check to see which way the lift would run if this value is positive
    // Make sure that the lift is giving very little power when it is first being tested
    double liftPosition = GetLiftInches();

    // Sets the requested speed to the value from the joystick
    SetRequestedSpeed(-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));

    // Scales the requested speed down to make sure the lift does not move too quickly
    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed *= 0.05;
        } else {
            m_requestedSpeed *= 0.2;
        }
        SetRequestedPosition(liftPosition);
    }

    double liftRequestedPosition = m_requestedPosition;

    // Stops the motors if we are at the top or bottom position, and resets encoders at the bottom of the lift
    if (m_requestedSpeed > 0 && liftPosition > m_topLimit.Get()) {
        m_requestedSpeed = 0;
        SetRequestedPosition(m_topLimit.Get());
    } else if (LiftDown()) {
        if(m_requestedSpeed < 0) {
            m_requestedSpeed = 0;
            SetRequestedPosition(0);
        }
        ResetEncoder();
    }

    // Checks requested speed and either sets motors based on motion magic or percent output based on magnitude
    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        m_rightLiftMotor.Set(ControlMode::PercentOutput, m_requestedSpeed);
    } else {
        m_rightLiftMotor.Set(ControlMode::MotionMagic, liftRequestedPosition);
    }
}

// Sets the requested position and modifies if the desired position is below the minimum
// or above the maximum
void LiftSubsystem::SetRequestedPosition(double positionInInches){
    auto position = (int)(positionInInches * m_ticksPerInch.Get());
    position = max(position, 0);
    position = min(position, (int)(m_topLimit.Get() * m_ticksPerInch.Get()));
    m_requestedPosition = position;
}

// Sets the speed to the desired speed

void LiftSubsystem::SetRequestedSpeed(double speed){
    m_requestedSpeed = speed;
}

// Returns the current position in ticks

double LiftSubsystem::GetLiftPosition(){
    return m_rightLiftMotor.GetSelectedSensorPosition(0);
}

// Returns the current position in inches

double LiftSubsystem::GetLiftInches(){
    return GetLiftPosition() / m_ticksPerInch.Get();
}

//Returns whether the lift is at the bottom or not 

bool LiftSubsystem::LiftDown() {
    return m_limitSwitch.Get();
}

// Resets lift encoders

void LiftSubsystem::ResetEncoder(){
    m_rightLiftMotor.SetSelectedSensorPosition(0, 0, 0);
}

// Below are functions that set the lift to the height of the desired field target

void LiftSubsystem::SetFirstLevelHatchHeight() {
    SetRequestedPosition(m_firstLevelHatch.Get());
}

void LiftSubsystem::SetSecondLevelHatchHeight() {
    SetRequestedPosition(m_secondLevelHatch.Get());
}

void LiftSubsystem::SetThirdLevelHatchHeight() {
    SetRequestedPosition(m_thirdLevelHatch.Get());
}

void LiftSubsystem::SetFirstLevelCargoHeight() {
    SetRequestedPosition(m_firstLevelHatch.Get());
}

void LiftSubsystem::SetSecondLevelCargoHeight() {
    SetRequestedPosition(m_secondLevelHatch.Get());
}

void LiftSubsystem::SetThirdLevelCargoHeight() {
    SetRequestedPosition(m_thirdLevelHatch.Get());
}

void LiftSubsystem::SetCargoShipCargoLevel() {
    SetRequestedPosition(m_cargoShipCargoLevel.Get());
}

void LiftSubsystem::SetCargoShipHatchLevel() {
    SetRequestedPosition(m_cargoShipHatchLevel.Get());
}

void LiftSubsystem::Set

// Below are 8 functions that check if the lift is within 2 inches of the desired field target

bool LiftSubsystem::IsFirstLevelCargo() {
    return abs(GetLiftInches() - m_firstLevelCargo.Get()) < 2;
}

bool LiftSubsystem::IsFirstLevelHatch() {
    return abs(GetLiftInches() - m_firstLevelHatch.Get()) < 2;
}

bool LiftSubsystem::IsSecondLevelCargo() {
    return abs(GetLiftInches() - m_secondLevelCargo.Get()) < 2;
}

bool LiftSubsystem::IsSecondLevelHatch() {
    return abs(GetLiftInches() - m_secondLevelHatch.Get()) < 2;
}

bool LiftSubsystem::IsThirdLevelCargo() {
    return abs(GetLiftInches() - m_thirdLevelCargo.Get()) < 2;
}

bool LiftSubsystem::IsThirdLevelHatch() {
    return abs(GetLiftInches() - m_thirdLevelHatch.Get()) < 2;
}

bool LiftSubsystem::IsCargoShipCargoLevel() {
    return abs(GetLiftInches()) - m_cargoShipCargoLevel.Get()) < 2;
}

bool LiftSubsystem::IsCargoShipHatchLevel() {
    return abs(GetLiftInches()) - m_cargoShipHatchLevel.Get()) < 2;
}