#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

//TODO:Fill these in with actual port numbers
HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidPunchOne(0, HATCH_SCORER_PUNCH_IN, HATCH_SCORER_PUNCH_OUT),
                                               m_IntakeMotor(HATCH_SCORER_MOTOR),
                                               m_punchSeconds("Hatch Scorer Punch Time (seconds)"),
                                               m_retractSeconds("Hatch Scorer Retract Time (seconds)"),
                                               m_toggleClawSeconds("Claw Toggle Time (seconds)") {

}

void HatchScorerSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
}

void HatchScorerSubsystem::teleopInit() {
    
}

void HatchScorerSubsystem::teleop() {
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) || GetIsScoring()) {
        ScoreHatchOnRocket();
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        OuttakeHatch();
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        IntakeHatch();
    } else {
        StopMotors();
    }
}

void HatchScorerSubsystem::ScoreHatchOnRocket() {
    if (!m_isScoring){
        //not yet started
        m_isScoring = true;
        ExtendPunch();
        OuttakeHatch();
        StartTimer();
    }  else {
        //we have started 
        //get timer value, check against desired value.
        if(GetTime() >= m_punchSeconds.Get() && !m_isToggling) {
            m_isToggling = true;
        }
        else if (GetTime() >= m_toggleClawSeconds.Get() && !m_isRetracting) {
            RetractPunch();
            m_isRetracting = true;
        } else if (GetTime() >= m_retractSeconds.Get()) {
            m_isScoring = false;
            m_isRetracting = false;
            m_isToggling = false; 
        }
    }
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

void HatchScorerSubsystem::IntakeHatch() {
    m_IntakeMotor.Set(ControlMode::PercentOutput, -0.6);
}

void HatchScorerSubsystem::OuttakeHatch() {
    m_IntakeMotor.Set(ControlMode::PercentOutput, 1);
}

void HatchScorerSubsystem::StopMotors() {
    m_IntakeMotor.Set(ControlMode::PercentOutput, 0);
}

bool HatchScorerSubsystem::GetIsScoring() {
    return m_isScoring;
}

bool HatchScorerSubsystem::GetIsLoading() {
    return m_isLoading;
}
