#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

//TODO:Fill these in with actual port numbers
HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidExtendOne(0, 0, 0),
                                               m_solenoidExtendTwo(0, 0, 0),
                                               m_solenoidClaw(0, 0, 0) {

}

void HatchScorerSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::Y_BUTTON);
}

void HatchScorerSubsystem::teleopInit() {
}

void HatchScorerSubsystem::teleop() {
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        ActuateClaw();
    }
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::Y_BUTTON)) {
        SetClawState();        
    }
}

void HatchScorerSubsystem::ActuateClaw() {
    if (!isExtended) {
        m_solenoidExtendOne.Set(frc::DoubleSolenoid::kForward);
        m_solenoidExtendTwo.Set(frc::DoubleSolenoid::kForward);
        isExtended = true;
    } else {
        m_solenoidExtendOne.Set(frc::DoubleSolenoid::kReverse);
        m_solenoidExtendTwo.Set(frc::DoubleSolenoid::kReverse);
        isExtended = false;
    }
}

void HatchScorerSubsystem::SetClawState() {
    if (!isOpen) {
        m_solenoidClaw.Set(frc::DoubleSolenoid::kForward);
        isOpen = true;

    } else {
        m_solenoidClaw.Set(frc::DoubleSolenoid::kReverse);
        isOpen = false;
    }
}
