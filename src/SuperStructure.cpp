#include <SuperStructure.h>
#include "Robot.h"

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
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::BACK_BUTTON);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_N);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_S);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::DPAD_W);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::START_BUTTON);
    // TODO: Change Auton Routines to move to the first level hatch
    m_liftState = LiftState::LiftUnknownLevel;
    m_wantedLiftState = LiftState::LiftUnknownLevel;
    m_cargoState = CargoState::CargoNeutral;
    m_wantedCargoState = CargoState::CargoNeutral;
    m_hatchScorerState = HatchScorerState::HatchScorerNeutral;
    m_wantedHatchScorerState = HatchScorerState::HatchScorerNeutral;
    // m_hatchIntake = HatchIntakeState::HatchIntakeNeutral;
    // m_wantedHatchIntake = HatchIntakeState::HatchIntakeNeutral;
}

void SuperStructure::teleop() {

    // Lift Buttons
    // if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::Y_BUTTON)) {
    //     m_wantedLiftState = LiftState::LiftHatchThirdLevel;
    // } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
    //     m_wantedLiftState = LiftState::LiftHatchSecondLevel;
    // } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::A_BUTTON)) {
    //     m_wantedLiftState = LiftState::LiftHatchFirstLevel;
    // } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_N)) {
    //     m_wantedLiftState = LiftState::LiftCargoThirdLevel;
    // } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_W)) {
    //     m_wantedLiftState = LiftState::LiftCargoSecondLevel;
    // } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_S)) {
    //     m_wantedLiftState = LiftState::LiftCargoFirstLevel;
    // }
        
    // Cargo Buttons
    cout << "Iteration begins" << endl;
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
        m_wantedCargoState = CargoState::CargoIntake;
        cout<<"Setting cargo intake in" << endl;
    } else if (operatorJoystick->GetFallingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        m_wantedCargoState = CargoState::CargoNeutral;
        cout<<"Setting cargo intake off" << endl;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        m_wantedCargoState = CargoState::CargoOuttake;
        cout<<"Setting cargo intake out" << endl;
    }
    // } else if (operatorJoystick->GetFallingEdge(CORE::COREJoystick::JoystickButton::BACK_BUTTON)) {
    //     m_wantedCargoState = CargoNeutral;
    // }

    // Hatch Scorer Buttons
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        m_wantedHatchScorerState = HatchScorerState::HatchScorerIntake;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        m_wantedHatchScorerState = HatchScorerState::HatchScorerOuttake;
    }

    // Hatch Intake Buttons
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeState::HatchIntakeIntake;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeState::HatchIntakeOuttake;
    }
    
    LiftState newLiftState = m_liftState;
    CargoState newCargoState = m_cargoState;
    HatchIntakeState newHatchIntakeState = m_hatchIntakeState;
    HatchScorerState newHatchScorerState = m_hatchScorerState;

    switch (m_wantedLiftState) {
        case LiftState::LiftHatchFirstLevel:
            newLiftState = LiftHatchFirstLevel();
            break;
        case LiftState::LiftCargoFirstLevel:
            newLiftState = LiftCargoFirstLevel();
            break;
        case LiftState::LiftHatchSecondLevel:
            newLiftState = LiftHatchSecondLevel();
            break;
        case LiftState::LiftCargoSecondLevel:
            newLiftState = LiftCargoSecondLevel();
            break;
        case LiftState::LiftHatchThirdLevel:
            newLiftState = LiftHatchThirdLevel();
            break;
        case LiftState::LiftCargoThirdLevel:
            newLiftState = LiftCargoThirdLevel();
            break;
        default:
            newLiftState = LiftState::LiftUnknownLevel;
            break;
    }

    if (newLiftState == m_wantedLiftState) {
        m_wantedLiftState = LiftState::LiftUnknownLevel;
    }

    switch (m_wantedCargoState) {
        case CargoState::CargoIntake:
            newCargoState = CargoIntake();
            cout << "Cargo Intake" << endl;
            break;
        case CargoState::CargoOuttake:
            newCargoState = CargoOuttake();
            cout << "Cargo Outtake" << endl; 
            break;
        default:
            newCargoState = CargoState::CargoNeutral;
            m_cargoSubsystem->SetOff();
            cout << "Cargo Off" << endl;
            break;
    }
    
    if (newCargoState == m_wantedCargoState && newCargoState != CargoOuttake()) {
        m_wantedCargoState = CargoState::CargoNeutral;
    }

    switch (m_wantedHatchScorerState) {
        case HatchScorerState::HatchScorerIntake:
            newHatchScorerState = HatchScorerIntake();
            break;
        case HatchScorerState::HatchScorerOuttake:
            newHatchScorerState = HatchScorerOuttake();
            break;
        default:
            newHatchScorerState = HatchScorerState::HatchScorerNeutral;
            break;
    }
    if (newHatchScorerState == m_wantedHatchScorerState) {
        m_wantedHatchScorerState = HatchScorerState::HatchScorerNeutral;
    }

    // switch (m_wantedHatchIntakeState) {
    //     case HatchIntakeState::HatchIntakeIntake:
    //         newHatchIntakeState = HatchIntakeIntake();
    //         break;
    //     case HatchIntakeState::HatchIntakeOuttake:
    //         newHatchIntakeState = HatchIntakeOuttake();
    //         break;
    //     default:
    //         newHatchIntakeState = HatchIntakeState::HatchIntakeNeutral;
    //         break;
    // }
    // if (newHatchIntakeState == m_wantedHatchIntakeState) {
    //     m_wantedHatchIntakeState = HatchIntakeState::HatchIntakeNeutral;
    // }

    if (newLiftState != m_liftState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_liftState) + " to " + to_string((int)newLiftState));
        m_liftState = newLiftState;
    }

    if (newCargoState != m_cargoState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_cargoState) + " to " + to_string((int)newCargoState));
        m_cargoState = newCargoState;
    }

    if (newHatchIntakeState != m_hatchIntakeState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_hatchIntakeState) + " to " + to_string((int)newHatchIntakeState));
        m_hatchIntakeState = newHatchIntakeState;
    }

    if (newHatchScorerState != m_hatchScorerState) {
        CORELog::LogInfo("Changing states from " + to_string((int)m_hatchScorerState) + " to " + to_string((int)newHatchScorerState));
        m_hatchScorerState = newHatchScorerState;
    }
}

LiftState SuperStructure::LiftHatchFirstLevel() {
    m_liftSubsystem->SetFirstLevelHatchHeight();
    if (m_liftSubsystem->IsFirstLevelHatch()) {
        return LiftState::LiftHatchFirstLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoFirstLevel() {
    m_liftSubsystem->SetFirstLevelCargoHeight();
    if (m_liftSubsystem->IsFirstLevelCargo()) {
        return LiftState::LiftCargoFirstLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchSecondLevel() {
    m_liftSubsystem->SetSecondLevelHatchHeight();
    if (m_liftSubsystem->IsSecondLevelHatch()) {
        return LiftState::LiftHatchSecondLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoSecondLevel() {
    m_liftSubsystem->SetSecondLevelCargoHeight();
    if (m_liftSubsystem->IsSecondLevelCargo()) {
        return LiftState::LiftCargoSecondLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchThirdLevel() {
    m_liftSubsystem->SetThirdLevelHatchHeight();
    if (m_liftSubsystem->IsThirdLevelHatch()) {
        return LiftState::LiftHatchThirdLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoThirdLevel() {
    m_liftSubsystem->SetThirdLevelCargoHeight();
    if (m_liftSubsystem->IsThirdLevelCargo()) {
        return LiftState::LiftCargoThirdLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoShipCargoLevel() {
    m_liftSubsystem->SetCargoShipCargoLevel();
    if (m_liftSubsystem->IsCargoShipHatchLevel()) {
        return LiftState::LiftCargoShipHatchLevel;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftLevelToIntakeCargo() {
    m_liftSubsystem->SetCargoIntakeLevelHeight();
    if (m_liftSubsystem->IsLevelToCargoIntake()) {
        return LiftState::LiftLevelToCargoIntake;
    } else {
        return LiftState::LiftUnknownLevel;
    }
}

CargoState SuperStructure::CargoIntake() {
    if (m_cargoSubsystem->IsCargoSecured()) {
        m_cargoSubsystem->SetOff();
        // if(m_liftSubsystem->IsLevelAfterCargoIntake()){
        return CargoState::CargoNeutral;
        // } else {
        //     m_liftSubsystem->SetLevelAfterCargoIntake();
        //     return CargoState::CargoIntake;
        // }
        
    } else {
        m_cargoSubsystem->SetIntake();
        return CargoState::CargoIntake;
    }
}

CargoState SuperStructure::CargoOuttake() {
    m_cargoSubsystem->SetOuttake();
    return CargoState::CargoOuttake;
} 
CargoState SuperStructure::CargoNeutral() {
    m_cargoSubsystem->SetOff();
    return CargoState::CargoNeutral;
}

HatchScorerState SuperStructure::HatchScorerIntake() {
    m_hatchScorerSubsystem->ScoreHatch();
    if (m_hatchScorerSubsystem->GetIsOperating()) {
        return HatchScorerState::HatchScorerIntake;
    } else {
        return HatchScorerState::HatchScorerNeutral;
    }
}

HatchScorerState SuperStructure::HatchScorerOuttake() {
    m_hatchScorerSubsystem->LoadHatch();
    if (m_hatchScorerSubsystem->GetIsOperating()) {
        return HatchScorerState::HatchScorerOuttake;
    } else {
        return HatchScorerState::HatchScorerNeutral;
    }
}

// HatchIntakeState SuperStructure::HatchIntakeIntake() {
// }

// HatchIntakeState SuperStructure::HatchIntakeOuttake() {
// }
