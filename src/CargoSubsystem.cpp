#include <CargoSubsystem.h>

CargoSubsystem::CargoSubsystem() : m_rightSideIntake(RIGHT_INTAKE_PORT),
                                   m_leftSideIntake(LEFT_INTAKE_PORT),
                                   m_cargoLimitSwitch(CARGO_LIMIT_SWITCH_PORT) {
}

void CargoSubsystem::robotInit() {
    m_rightSideIntake.Set(ControlMode::PercentOutput, 0);
    m_leftSideIntake.Set(ControlMode::PercentOutput, 0);
    m_leftSideIntake.SetInverted(true);
    m_rightSideIntake.SetInverted(false);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
}

void CargoSubsystem::teleopInit() {
}

void CargoSubsystem::teleop() {
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON) && IsCargoSecured()) {
        SetIntake();
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        SetOuttake();
    } else {
        m_rightSideIntake.Set(ControlMode::PercentOutput, 0);
        m_leftSideIntake.Set(ControlMode::PercentOutput, 0);
    }
}

//spins wheels to intake the cargo
void CargoSubsystem::SetIntake() {
    m_rightSideIntake.Set(ControlMode::PercentOutput, 0.2);
    m_leftSideIntake.Set(ControlMode::PercentOutput, 0.2);
}

//returns true if the intake is intaking
bool CargoSubsystem::IsCargoSecured() {
    return !m_cargoLimitSwitch.Get();
}

//spins wheels to outtake the cargo
void CargoSubsystem::SetOuttake() {
    m_rightSideIntake.Set(ControlMode::PercentOutput, -0.2);
    m_leftSideIntake.Set(ControlMode::PercentOutput, -0.2);
}