#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidPunchOne(0, HATCH_SCORER_PUNCH_IN, HATCH_SCORER_PUNCH_OUT),
                                               m_solenoidClaw(0, HATCH_SCORER_CLAW_IN, HATCH_SCORER_CLAW_OUT),
                                               m_punchSeconds("Hatch Scorer Punch Time (seconds)"),
                                               m_retractSeconds("Hatch Scorer Retract Time (seconds)"),
                                               m_toggleClawSeconds("Claw Toggle Time (seconds)") {

}

void HatchScorerSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
}

void HatchScorerSubsystem::teleopInit() {
    OpenClaw();
}

void HatchScorerSubsystem::teleop() {
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) || GetIsScoring()) {
        ScoreHatch();
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER) || GetIsLoading()) {
        LoadHatch();
    }
}

void HatchScorerSubsystem::ScoreHatch() {
    if (!m_isScoring){
        //not yet started
        m_isScoring = true;
        ExtendPunch();
        StartTimer();
    }  else {
        //we have started 
        //get timer value, check against desired value.
        if(GetTime() >= m_punchSeconds.Get() && !m_isToggling) {
            //CloseClaw();
            OpenClaw();
            m_isToggling = true;
        }
        else if (GetTime() >= m_toggleClawSeconds.Get() && !m_isRetracting) {
            RetractPunch();
            m_isRetracting = true;
        } else if (GetTime() >= m_retractSeconds.Get()) {
            //OpenClaw();
            m_isScoring = false;
            m_isRetracting = false;
            m_isToggling = false; 
        }
    }

}

void HatchScorerSubsystem::LoadHatch() {
    ToggleClaw();
}

void HatchScorerSubsystem::ExtendPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kReverse);
    m_isExtended = true;
}

void HatchScorerSubsystem::RetractPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kForward);
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
        OpenClaw();
    } else {
        CloseClaw();
    }
}

void HatchScorerSubsystem::OpenClaw() {
    m_solenoidClaw.Set(frc::DoubleSolenoid::kReverse);
    m_isOpen = true;
}

void HatchScorerSubsystem::CloseClaw() {
    m_solenoidClaw.Set(frc::DoubleSolenoid::kForward);
    m_isOpen = false;
}

bool HatchScorerSubsystem::GetIsScoring() {
    return m_isScoring;
}

bool HatchScorerSubsystem::GetIsLoading() {
    return m_isLoading;
}
