#include <HatchIntakeSubsystem.h>

#include "Robot.h"

HatchIntakeSubsystem::HatchIntakeSubsystem() : m_hatchIntake(HATCH_INTAKE_PORT),
                                               m_hatchIntakeSolenoid(0, 12),
                                               m_photoeye(HATCH_INTAKE_PHOTOEYE)
{
    isDown = false;
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

// Changes the orientation of the hatch intake by 90 degrees.
void HatchIntakeSubsystem::ToggleHatchIntake(){
    if(!isDown){
        m_hatchIntakeSolenoid.Set(frc::DoubleSolenoid::kForward);
        isDown = true;
    }
    else{
        m_hatchIntakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
        isDown = false;
    }
    
}

// Returns true if the hatch is completely in, else false.
bool HatchIntakeSubsystem::GetHatchState(){
    return m_photoeye.Get() != 0;
}
