#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

//TODO:Fill these in with actual port numbers
HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidPunchOne(0, HATCH_SCORER_PUNCH_IN, HATCH_SCORER_PUNCH_OUT),
                                               m_solenoidClaw(0, HATCH_SCORER_CLAW_IN, HATCH_SCORER_CLAW_OUT) {

}

void HatchScorerSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::Y_BUTTON);
}

void HatchScorerSubsystem::teleopInit() {
}

void HatchScorerSubsystem::teleop() {
    // int iterationCount;
    // if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
    //     PunchHatch();
    //     StartTimer();
    //     iterationCount++;
    // }
    // if (GetTime() >= 3 && iterationCount == 1) {
    //     ToggleClaw();
    //     StartTimer();
    //     iterationCount++;
    // }
    // if (GetTime() >= 3 && iterationCount == 2) {
    //      PunchHatch();
    //      m_delayTimer.Reset();
    //      iterationCount = 0;
    // }
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        PunchHatch();
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::Y_BUTTON)) {
        ToggleClaw();
    }
}
void HatchScorerSubsystem::PunchHatch() {
    if (!m_isExtended) {
        m_solenoidPunchOne.Set(frc::DoubleSolenoid::kForward);
        m_isExtended = true;
    } else {
        m_solenoidPunchOne.Set(frc::DoubleSolenoid::kReverse);
        m_isExtended = false;
    }
}

void HatchScorerSubsystem::StartTimer() {
    m_delayTimer.Reset();
    m_delayTimer.Start();
}

double HatchScorerSubsystem::GetTime() {
    return m_delayTimer.Get(); 
}

void HatchScorerSubsystem::ToggleClaw() {
    if (!m_isOpen) {
        m_solenoidClaw.Set(frc::DoubleSolenoid::kForward);
        m_isOpen = true;

    } else {
        m_solenoidClaw.Set(frc::DoubleSolenoid::kReverse);
        m_isOpen = false;
    }
}
