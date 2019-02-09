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

void HatchIntakeSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    
    m_hatchActuator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_hatchActuator.SetSelectedSensorPosition(0, 0, 0);
    
    //Uncertain of the necessity of the line below
    m_hatchActuator.SetSensorPhase(true);
}

void HatchIntakeSubsystem::teleopInit() {
   
}

void HatchIntakeSubsystem::teleop() {
    // Actuates the intake down when the button is initially pressed
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) || operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
        SetHatchActuatorDown();
    }

    // Changes the diection of the intake wheel based on which button is pressed, the motor
    // turns off when the hatch is either in or out depending on the button pressed.
    // Right Button is spit hatch out and Right Trigger is take hatch in
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        SetIntake(false, HatchIn());
    }
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        SetIntake(true, !HatchIn());
    }

    // Actuates the intake back up when the button is no longer being pressed
    if(operatorJoystick->GetFallingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON) || operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
        SetHatchActuatorUp();
    }
}

void HatchIntakeSubsystem::SetIntake(bool setIntakeDirection, bool conditionMet) {
    if(setIntakeDirection) {
        if(conditionMet) {
            m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
        }else {         
            m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
        }
    } else {
        if(conditionMet) {
            m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
        }else {        
            m_hatchActuator.Set(ControlMode::PercentOutput, -0.2);
        }
        }
}

//Actuates the intake up, deadbanded.
void HatchIntakeSubsystem::SetHatchActuatorUp() {
    if (m_hatchActuatorDeadband.Get() <= abs(m_actuatorTopLimit.Get() - m_hatchActuator.GetSelectedSensorPosition())) {
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    } else {
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

//Actuates the intake down, deadbanded.
void HatchIntakeSubsystem::SetHatchActuatorDown() {
    if (m_hatchActuatorDeadband.Get() <= abs(m_actuatorBottomLimit.Get() - m_hatchActuator.GetSelectedSensorPosition())) {
    m_hatchActuator.Set(ControlMode::PercentOutput, 0.2);
    } else {
        m_hatchActuator.Set(ControlMode::PercentOutput, 0.0);
    }
}

// Returns true if the hatch is completely in, else false.
bool HatchIntakeSubsystem::HatchIn() {
    return m_photoeye.Get() != 0;
}
