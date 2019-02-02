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

void LiftSubsystem::robotInit(){
    m_leftLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_rightLiftMotor.Set(ControlMode::PercentOutput, 0.0);
    m_leftLiftMotor.Follow(m_rightLiftMotor);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y);
}

void LiftSubsystem::teleopInit(){
    SetRequestedPosition(GetLiftInches());
    m_rightLiftMotor.ConfigMotionCruiseVelocity(m_cruiseVel.Get(), 0);
    m_rightLiftMotor.ConfigMotionAcceleration(m_maxAcel.Get(), 0);
}

void LiftSubsystem::teleop() {
    SmartDashboard::PutNumber("Lift requested position", m_requestedPosition);
    SmartDashboard::PutNumber("Lift position in inches", m_rightLiftMotor.GetSelectedSensorPosition(0) /
        m_ticksPerInch.Get());
    SmartDashboard::PutNumber("Lift position in ticks", m_rightLiftMotor.GetSelectedSensorPosition(0));
    // Add code to run the lift 
    // Check to see which way the lift would run if this value is positive
    // Make sure that the lift is giving very little power when it is first being tested
    double liftPosition = GetLiftInches();

    SetRequestedSpeed(operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_Y));

    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        if (m_requestedSpeed < 0) {
            m_requestedSpeed *= 0.1;
        } else {
            m_requestedSpeed *= 0.2;
        }
        SetRequestedPosition(liftPosition);
    }
    double liftRequestedPosition = m_requestedPosition;

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

    if (m_requestedSpeed < -0.01 || m_requestedSpeed > 0.1) {
        m_rightLiftMotor.Set(ControlMode::PercentOutput, m_requestedSpeed);
    } else {
        m_rightLiftMotor.Set(ControlMode::MotionMagic, liftRequestedPosition);
    }
}

void LiftSubsystem::SetRequestedPosition(double positionInInches){
    auto position = (int)(positionInInches * m_ticksPerInch.Get());
    position = max(position, 0);
    position = min(position, (int)(m_topLimit.Get() * m_ticksPerInch.Get()));
    m_requestedPosition = position;
}

void LiftSubsystem::SetRequestedSpeed(double speed){
    m_requestedSpeed = speed;
}

double LiftSubsystem::GetLiftPosition(){
    return m_rightLiftMotor.GetSelectedSensorPosition(0);
}

double LiftSubsystem::GetLiftInches(){
    return GetLiftPosition() / m_ticksPerInch.Get();
}

bool LiftSubsystem::LiftDown() {
    return m_limitSwitch.Get();
}

void LiftSubsystem::ResetEncoder(){
    m_rightLiftMotor.SetSelectedSensorPosition(0, 0, 0);
}

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