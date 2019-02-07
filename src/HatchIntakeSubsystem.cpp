#include <HatchIntakeSubsystem.h>

#include "Robot.h"

HatchIntakeSubsystem::HatchIntakeSubsystem() : m_hatchIntake(HATCH_INTAKE_PORT),
                                               m_hatchActuator(HATCH_ACTUATOR_PORT),
                                               m_photoeye(HATCH_INTAKE_PHOTOEYE)
                                               m_actautorBottomLimit("Bottom limit of the hatch intake")
                                               m_actautorTopLimit("Top limit of the hatch intake")
{
}

void HatchIntakeSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);

}

void HatchIntakeSubsystem::teleopInit(){
   
}

void HatchIntakeSubsystem::teleop(){
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)){
        SetIntakeOn();
    }else{
        SetIntakeOff();
    }
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
        ToggleHatchIntake();
    }
}

// Spins the wheels of the intake.
void HatchIntakeSubsystem::SetIntakeOn(){
    if(GetHatchState()){
        m_hatchIntake.Set(ControlMode::PercentOutput, 0.0);
    }else{
    m_hatchIntake.Set(ControlMode::PercentOutput, 0.2);
    }
}

// Turns hatch intake motor off.
void HatchIntakeSubsystem::SetIntakeOff(){
    m_hatchIntake.Set(ControlMode::PercentOutput, 0.0);
}

//Actuates the intake up.
void HatchIntakeSubsystem::HatchActuatorUp(){
    if(m_){
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    }
}

//Actuates the intake down.
void HatchIntakeSubsystem::HatchActuatorDown(){
    if(){
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    }
}

// Returns true if the hatch is completely in, else false.
bool HatchIntakeSubsystem::GetHatchState(){
    return m_photoeye.Get() != 0;
}
