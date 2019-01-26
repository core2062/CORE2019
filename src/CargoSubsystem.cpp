#include <CargoSubsystem.h>

#include "Robot.h"

CargoSubsystem::CargoSubsystem() {

}

void CargoSubsystem::robotInit(){
m_rightSideIntake.Set(ControlMode::PercentOutput, 0);
m_leftSideIntake.Set(ControlMode::PercentOutput, 0);
m_leftSideIntake.SetInverted(true);
m_rightSideIntake.SetInverted(false);
operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
operatorJoystick->registerButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
}

void CargoSubsystem::teleopInit(){
    
}

void CargoSubsystem::teleop(){
    
    if(isIntaking()){
        m_rightSideIntake.Set(ControlMode::PercentOutput, 0);
        m_leftSideIntake.Set(ControlMode::PercentOutput, 0);
    }
    else{
        if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {

        }else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {

        } else {
            m_rightSideIntake.Set(ControlMode::PercentOutput, 0);
         m_leftSideIntake.Set(ControlMode::PercentOutput, 0);
    }
    }
}

void CargoSubsystem::setIntake(){
    m_rightSideIntake.Set(ControlMode::PercentOutput, 0.2);
    m_leftSideIntake.Set(ControlMode::PercentOutput, 0.2);
}

bool CargoSubsystem::isIntaking(){
    if(m_cargoLimitSwitch.Get()){
        return true;
    }
    else{
        return false;
    }
}