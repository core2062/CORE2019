#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

//TODO:Fill these in with actual port numbers
HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidPunchOne(0, 0, 0),
                                               m_solenoidPunchTwo(0, 0, 0),
                                               m_solenoidClaw(0, 0, 0) {

}

void HatchScorerSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
}

void HatchScorerSubsystem::teleopInit() {
}

void HatchScorerSubsystem::teleop() {
   if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON) || !m_isOperating){
       TogglePunchHatch();
   }
}

void HatchScorerSubsystem::TogglePunchHatch() {
    if (!m_isOperating){
        //not yet started
        m_isOperating = true;
        ExtendPunch();
        ToggleClaw();
        StartTimer();
        //iterationCount++;
    }  else {
        //we have started 
        //get timer value, check against desired value.
        if (GetTime() >= 3 && !m_isRetracting) {
            RetractPunch();
            m_isRetracting = true;
        } else if (GetTime() >= 6) {
            m_isOperating = false;
            m_isRetracting = false;
        }
    }
}

void HatchScorerSubsystem::ExtendPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kForward);
    m_solenoidPunchTwo.Set(frc::DoubleSolenoid::kForward);
    m_isExtended = true;

}

void HatchScorerSubsystem::RetractPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kReverse);
    m_solenoidPunchTwo.Set(frc::DoubleSolenoid::kReverse);
    m_isExtended = false;


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
        openClaw();
    } else {
        closedClaw();
    }
}

void HatchScorerSubsystem::OpenClaw() {
    m_solenoidClaw.Set(frc::DoubleSolenoid::kForward);
    m_isOpen = true;
}

void HatchScorerSubsystem::CloseClaw() {
    m_solenoidClaw.Set(frc::DoubleSolenoid::kReverse);
    m_isOpen = false;
}
