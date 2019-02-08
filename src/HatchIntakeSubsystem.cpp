#include <HatchIntakeSubsystem.h>
#include <CORERobotlib.h>

#include "Robot.h"

HatchIntakeSubsystem::HatchIntakeSubsystem() : m_hatchIntake(HATCH_INTAKE_MOTOR_PORT),
                                               m_hatchActuator(HATCH_INTAKE_SOLENOID_PORT),
                                               m_photoeye(HATCH_INTAKE_PHOTOEYE),
                                               m_actuatorBottomLimit("Bottom limit of the hatch intake"),
                                               m_actuatorTopLimit("Top limit of the hatch intake")
{
}

void HatchIntakeSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    
    m_hatchIntake.SetNeutralMode(NeutralMode::Coast);
    m_hatchActuator.SetNeutralMode(NeutralMode::Brake);

    m_hatchActuator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_hatchActuator.SetSelectedSensorPosition(0, 0, 0);
    
    //Uncertain of the necessity of the line below
    m_hatchActuator.SetSensorPhase(true);
}

void HatchIntakeSubsystem::teleopInit(){
   
}

void HatchIntakeSubsystem::teleop(){
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)){
        SetIntakeOn();
    } else {
        SetIntakeOff();
    }
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
        if(m_hatchActuator.GetSelectedSensorPosition() == m_actuatorTopLimit.Get()){
            HatchActuatorDown();
        }else if(m_hatchActuator.GetSelectedSensorPosition() < m_actuatorBottomLimit.Get()){
            HatchActuatorUp();
        }
    }
}

// Spins the wheels of the intake.
void HatchIntakeSubsystem::SetIntakeOn(){
    if(GetHatchState()){
        m_hatchIntake.Set(ControlMode::PercentOutput, 0.0);
    } else {
    m_hatchIntake.Set(ControlMode::PercentOutput, 0.2);
    }
}

// Turns hatch intake motor off.
void HatchIntakeSubsystem::SetIntakeOff(){
    m_hatchIntake.Set(ControlMode::PercentOutput, 0.0);
}

//Actuates the intake up.
void HatchIntakeSubsystem::HatchActuatorUp(){
    if (m_hatchActuator.GetSelectedSensorPosition() < m_actuatorTopLimit.Get()){
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    } else {
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

//Actuates the intake down.
void HatchIntakeSubsystem::HatchActuatorDown(){
    if (m_hatchActuator.GetSelectedSensorPosition() > m_actuatorBottomLimit.Get()){
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    } else {
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

// Returns true if the hatch is completely in, else false.
bool HatchIntakeSubsystem::GetHatchState(){
    return m_photoeye.Get() != 0;
}
