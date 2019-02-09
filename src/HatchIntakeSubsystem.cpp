#include <HatchIntakeSubsystem.h>
#include <CORERobotlib.h>

#include "Robot.h"

HatchIntakeSubsystem::HatchIntakeSubsystem() : m_hatchIntake(HATCH_INTAKE_WHEEL_MOTOR_PORT),
                                               m_hatchActuator(HATCH_INTAKE_ACTUATOR_MOTOR_PORT),
                                               m_photoeye(HATCH_INTAKE_PHOTOEYE),
                                               m_actuatorBottomLimit("Bottom limit of the hatch intake"),
                                               m_actuatorTopLimit("Top limit of the hatch intake"),
                                               m_hatchActuatorDeadband("Deadband for the hatch actuator")
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
    // When the right trigger is pressed the intake actuates down and spins the intake wheels until it gets
    // a hatch then it actuates up.
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
        if(m_hatchActuator.GetSelectedSensorPosition() >= m_actuatorTopLimit.Get() - m_hatchActuatorDeadband.Get()){
            SetHatchActuatorDown();
        }
        if(m_hatchActuator.GetSelectedSensorPosition() <= m_actuatorBottomLimit.Get() + m_hatchActuatorDeadband.Get()){
            if(GetHatchState()){
                SetHatchActuatorUp();
            }else{
                SetIntake(true, !GetHatchState());
            }
        }
    }
    // When the right button is pressed, the intake actuates down and spits out the hatch and actuates up.
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)){
       if(m_hatchActuator.GetSelectedSensorPosition() >= m_actuatorTopLimit.Get() - m_hatchActuatorDeadband.Get()){
            SetHatchActuatorDown();
        }
        if(m_hatchActuator.GetSelectedSensorPosition() <= m_actuatorBottomLimit.Get() + m_hatchActuatorDeadband.Get()){
            if(!GetHatchState()){
                SetHatchActuatorUp();
            }else{
                SetIntake(false, GetHatchState());
            }
        }
    }
}

// When the hatch is in, the motors stop. setIntakeDirection determines direction, true is in, false is out.
void HatchIntakeSubsystem::SetIntake(bool setIntakeDirection, bool activation){
    if(activation){
        if(setIntakeDirection){
            m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
        } else{
            m_hatchActuator.Set(ControlMode::PercentOutput, -0.2);
        }
    } else{
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

//Actuates the intake up.
void HatchIntakeSubsystem::SetHatchActuatorUp(){
    if (m_hatchActuator.GetSelectedSensorPosition() < m_actuatorTopLimit.Get()){
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    } else {
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

//Actuates the intake down.
void HatchIntakeSubsystem::SetHatchActuatorDown(){
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
