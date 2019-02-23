#include <SuperStructure.h>

SuperStructure::SuperStructure() {
}

void SuperStructure::robotInit() {
    m_cargoSubsystem  = &Robot::GetInstance()->cargoSubsystem;
    m_hatchIntakeSubsystem = &Robot::GetInstance()->hatchIntakeSubsystem;
    m_hatchScorerSubsystem = &Robot::GetInstance()->hatchScorerSubsystem;
    m_liftSubsystem = &Robot::GetInstance()->liftSubsystem;
    }

void SuperStructure::teleopInit() {
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::A_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::B_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::X_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::Y_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_TRIGGER);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_N);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_S);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_W);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::START_BUTTON);
    // Set an initial system state
}

void SuperStructure::teleop() {
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::Y_BUTTON)) {
        m_wantedLiftState = LiftHatchThirdLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        m_wantedLiftState = LiftHatchSecondLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::A_BUTTON)) {
        m_wantedLiftState = LiftHatchFirstLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_N)) {
        m_wantedLiftState = LiftCargoThirdLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_W)) {
        m_wantedLiftState = LiftCargoSecondLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_S)) {
        m_wantedLiftState = LiftCargoFirstLevel;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
        m_wantedCargoState = CargoIntake;
    }
    
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        m_wantedCargoState = CargoOutake;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        m_wantedHatchScorerState = HatchScorerIntake;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        m_wantedHatchScorerState = HatchScorerOutake;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeIntake;
    }
    
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeOutake;
    }
}

void SuperStructure::PostLoopTask() {
    LiftState newLiftState = m_liftState;
    CargoState newCargoState = m_cargoState;
    HatchIntakeState newHatchIntakeState = m_hatchIntakeState;
    HatchScorerState newHatchScorerState = m_hatchScorerState;

    switch(m_wantedLiftState) {

	case LiftState::LiftHatchFirstLevel:
        newLiftState = liftHatchFirstLevel();
        break;

	case LiftState::LiftCargoFirstLevel:
	    newLiftState = liftCargoFirstLevel();
        break;

    case LiftState::LiftHatchSecondLevel:
	    newLiftState = liftHatchSecondLevel();
        break;

    case LiftState::LiftCargoSecondLevel:
	    newLiftState = liftCargoSecondLevel();
        break;

    case LiftState::LiftHatchThirdLevel:
	    newLiftState = liftHatchThirdLevel();
        break;

    case LiftState::LiftCargoThirdLevel:
	    newLiftState = liftCargoThirdLevel();
        break;
    
    default:
        newLiftState = LiftUnknownLevel;
        break;
    }

    switch(m_wantedCargoState) {
    
    case CargoState::CargoIntake:
	    newCargoState = cargoIntake();
        break;

    case CargoState::CargoOutake:
	    newCargoState = cargoOutake();
        break;
    }

    switch(m_wantedHatchIntakeState) {
    
    case HatchIntakeState::HatchIntakeIntake:
	    newHatchIntakeState = hatchIntakeIntake();
        break;

    case HatchIntakeState::HatchIntakeOutake:
	    newHatchIntakeState = hatchIntakeOutake();
        break;
        
    default:
        newHatchIntakeState = HatchIntakeNeutral;
        break;
    }

    switch(m_wantedHatchScorerState) {
    
    case HatchScorerState::HatchScorerIntake:
	    newHatchScorerState = hatchScorerIntake();
        break;

    case HatchScorerState::HatchScorerOutake:
        newHatchScorerState = hatchScorerOutake();
        break;

    default:
        newHatchScorerState = HatchScorerNeutral;
        break;
    }

    if(newLiftState != m_liftState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_liftState) + " to " + to_string((int)newLiftState));
        m_liftState = newLiftState;
    }
    
    if(newCargoState != m_cargoState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_cargoState) + " to " + to_string((int)newCargoState));
        m_cargoState = newCargoState;
    }
    
    if(newHatchIntakeState != m_hatchIntakeState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_hatchIntakeState) + " to " + to_string((int)newHatchIntakeState));
        m_hatchIntakeState = newHatchIntakeState;
    }

    if(newHatchScorerState != m_hatchScorerState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_hatchScorerState) + " to " + to_string((int)newHatchScorerState));
        m_hatchScorerState = newHatchScorerState;
    }
}

void SuperStructure::setLiftWantedState(LiftState wantedState) {
    m_wantedLiftState = wantedState;
}

void SuperStructure::setCargoWantedState(CargoState wantedState) {
    m_wantedCargoState = wantedState;
}

void SuperStructure::setHatchIntakeWantedState(HatchIntakeState wantedState) {
    m_wantedHatchIntakeState = wantedState;
}

void SuperStructure::setHatchScorerWantedState(HatchScorerState wantedState) {
    m_wantedHatchScorerState = wantedState;
}

LiftState SuperStructure::LiftHatchFirstLevel() {
    m_liftSubsystem->SetFirstLevelHatchHeight();
    if(m_liftSubsystem->IsFirstLevelHatch()){
        return LiftHatchFirstLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoFirstLevel() {
    m_liftSubsystem->SetFirstLevelCargoHeight();
    if(m_liftSubsystem->IsFirstLevelCargo()){
        return LiftCargoFirstLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchSecondLevel() {
    m_liftSubsystem->SetSecondLevelHatchHeight();
    if(m_liftSubsystem->IsSecondLevelHatch()){
        return LiftHatchSecondLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoSecondLevel() {
    m_liftSubsystem->SetSecondLevelCargoHeight();
    if(m_liftSubsystem->IsSecondLevelCargo()){
        return LiftCargoSecondLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchThirdLevel() {
    m_liftSubsystem->SetThirdLevelHatchHeight();
    if(m_liftSubsystem->IsThirdLevelHatch()){
        return LiftHatchThirdLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoThirdLevel() {
    m_liftSubsystem->SetThirdLevelCargoHeight();
    if(m_liftSubsystem->IsThirdLevelCargo()){
        return LiftCargoThirdLevel;
    } else {
        return LiftUnknownLevel;
    }
}

CargoState SuperStructure::CargoIntake() {
    if(cargoSubsystem.IsCargoSecured()){
        m_cargoSubsystem->SetOff();
        m_liftSubsystem->SetCargoLiftLevel();
        if(m_liftSubsystem->IsCargoIntakeLift()){
            return CargoNeutral;
        } else {
            return CargoLift;
        }
    } else {
        m_cargoSubsystem->SetIntake();
        return CargoIntake;
    }

}

CargoState SuperStructure::CargoOutake() {
    m_cargoSubsystem->SetOuttake();
    return CargoNeutral;
}

// HatchIntakeState SuperStructure::HatchIntakeIntake() {
   
// }

// HatchIntakeState SuperStructure::HatchIntakeOutake() {

// }

// HatchScorerState SuperStructure::HatchScorerIntake() {
    
// }

// HatchScorerState SuperStructure::HatchScorerOutake() {

// }
    
    // if(!liftSubsystem.IsThirdLevelCargo() && m_stepState == LiftNotThirdLevel){   
    //     // Want to check state against wanted state. If current state is the same as wanted state, do nothing. If not, move to wanted state and check state.
    //     m_liftSubsystem->SetThirdLevelCargoHeight();

    //     //spin cargo in reverse to eject cargo into rocket ship
    // } else {
    //     m_state = LiftThirdLevel;
    //     m_cargoSubsystem->SetOuttake();
    //     thirdLevel = false;
    //     StartTimer();
        
    //     // Go down to the first level
    //     if(GetTime() > 2 && ){
    //         //set the lift to the default state
    //         m_liftSubsystem->SetFirstLevelCargoHeight();
    //     }
        
    // }
    // }
}
void SuperStructure::StartTimer() {
    m_delayTimer.Reset();
    m_delayTimer.Start();
}


double HatchScorerSubsystem::GetTime() {
    return m_delayTimer.Get(); 
}