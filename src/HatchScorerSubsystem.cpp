#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidPunchOne(0, HATCH_SCORER_PUNCH_IN, HATCH_SCORER_PUNCH_OUT),
                                               m_solenoidClaw(0, HATCH_SCORER_CLAW_IN, HATCH_SCORER_CLAW_OUT),
                                               m_punchSeconds("Hatch Scorer Punch Time (seconds)", 1.5),
                                               m_retractSeconds("Hatch Scorer Retract Time (seconds)", 1.5) {

}

void HatchScorerSubsystem::robotInit() {
}

void HatchScorerSubsystem::teleopInit() {
}

void HatchScorerSubsystem::teleop() {
}

void HatchScorerSubsystem::ScoreHatch() {
    if (!m_isOperating){
        //not yet started
        m_isOperating = true;
        ExtendPunch();
        CloseClaw();
        StartTimer();
    }  else {
        //we have started 
        //get timer value, check against desired value.
        if (GetTime() >= m_punchSeconds.Get() && !m_isRetracting) {
            RetractPunch();
            m_isRetracting = true;
        } else if (GetTime() >= m_retractSeconds.Get()) {
            m_isOperating = false;
            m_isRetracting = false; 
        }
    }
}

void HatchScorerSubsystem::LoadHatch() {
    if (!m_isOperating){
        //not yet started
        m_isOperating = true;
        ExtendPunch();
        OpenClaw();
        StartTimer();
    }  else {
        //we have started 
        //get timer value, check against desired value.
        if (GetTime() >= m_punchSeconds.Get() && !m_isRetracting) {
            RetractPunch();
            m_isRetracting = true;
        } else if (GetTime() >= m_retractSeconds.Get()) {
            m_isOperating = false;
            m_isRetracting = false; 
        }
    }
}

void HatchScorerSubsystem::ExtendPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kForward);
    m_isExtended = true;
}

void HatchScorerSubsystem::RetractPunch() {
    m_solenoidPunchOne.Set(frc::DoubleSolenoid::kReverse);
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
    m_solenoidClaw.Set(frc::DoubleSolenoid::kForward);
    m_isOpen = true;
}

void HatchScorerSubsystem::CloseClaw() {
    m_solenoidClaw.Set(frc::DoubleSolenoid::kReverse);
    m_isOpen = false;
}

bool HatchScorerSubsystem::GetIsOperating() {
    return m_isOperating;
}
