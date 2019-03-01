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
    // TODO: Change Auton Routines to move to the first level hatch
    m_liftState = LiftUnknownLevel;
    m_cargoState = CargoNeutral;
    // m_HatchIntake = HatchIntakeNeutral;
    // m_HatchScorer = HatchScorerNeutral;
}

void SuperStructure::teleop() {
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::Y_BUTTON)) {
        m_wantedLiftState = LiftHatchThirdLevel;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        m_wantedLiftState = LiftHatchSecondLevel;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::A_BUTTON)) {
        m_wantedLiftState = LiftHatchFirstLevel;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_N)) {
        m_wantedLiftState = LiftCargoThirdLevel;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_W)) {
        m_wantedLiftState = LiftCargoSecondLevel;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::DPAD_S)) {
        m_wantedLiftState = LiftCargoFirstLevel;
    }

    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
        m_wantedCargoState = CargoIntake;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        m_wantedCargoState = CargoOutake;
    } else if (operatorJoystick->GetFallingEdge(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        m_wantedCargoState = CargoNeutral;
    }

    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        m_wantedHatchScorerState = HatchScorerIntake;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        m_wantedHatchScorerState = HatchScorerOutake;
    }

    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeIntake;
    } else if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
        m_wantedHatchIntakeState = HatchIntakeOutake;
    }
    PostLoopTask();
}

void SuperStructure::PostLoopTask() {
    LiftState newLiftState = m_liftState;
    CargoState newCargoState = m_cargoState;
    HatchIntakeState newHatchIntakeState = m_hatchIntakeState;
    HatchScorerState newHatchScorerState = m_hatchScorerState;

    switch (m_wantedLiftState) {
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

    if (newLiftState == m_wantedLiftState) {
        m_wantedLiftState = LiftUnknownLevel;
    }

    switch (m_wantedCargoState) {
        case CargoState::CargoIntake:
            newCargoState = cargoIntake();
            break;
        case CargoState::CargoOutake:
            newCargoState = cargoOutake();
            break;
        default:
            newCargoState = CargoNeutral;
            m_cargoSubsystem.SetOff();
            break;
    }

    if (newCargoState == m_wantedCargoState) {
        m_wantedCargoState = CargoNeutral;
    }

    switch (m_wantedHatchIntakeState) {
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

    if (newHatchIntakeState == m_wantedHatchScorerState) {
        m_wantedHatchIntakeState = HatchIntakeNeutral;
    }

    switch (m_wantedHatchScorerState) {
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

    if (newHatchScorerState == m_wantedHatchScorerState) {
        m_wantedHatchScorerState = HatchScorerNeutral;
    }

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
        return LiftHatchFirstLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoFirstLevel() {
    m_liftSubsystem->SetFirstLevelCargoHeight();
    if (m_liftSubsystem->IsFirstLevelCargo()) {
        return LiftCargoFirstLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchSecondLevel() {
    m_liftSubsystem->SetSecondLevelHatchHeight();
    if (m_liftSubsystem->IsSecondLevelHatch()) {
        return LiftHatchSecondLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoSecondLevel() {
    m_liftSubsystem->SetSecondLevelCargoHeight();
    if (m_liftSubsystem->IsSecondLevelCargo()) {
        return LiftCargoSecondLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftHatchThirdLevel() {
    m_liftSubsystem->SetThirdLevelHatchHeight();
    if (m_liftSubsystem->IsThirdLevelHatch()) {
        return LiftHatchThirdLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::LiftCargoThirdLevel() {
    m_liftSubsystem->SetThirdLevelCargoHeight();
    if (m_liftSubsystem->IsThirdLevelCargo()) {
        return LiftCargoThirdLevel;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::CargoLiftLevel() {
    m_liftSubsystem->SetCargoLiftLevel();
    if (m_liftSubsystem->IsCargoIntakeLift()) {
        return LiftCargoAfterIntake;
    } else {
        return LiftUnknownLevel;
    }
}

LiftState SuperStructure::CargoIntakeLiftLevel() {
    m_liftSubsystem->SetCargoIntakeLevelHeight();
    if (m_liftSubsystem->IsCargoIntakeLift()) {
        return LiftCargoIntake;
    } else {
        return LiftUnknownLevel;
    }
}

CargoState SuperStructure::CargoIntake() {
    if (cargoSubsystem.IsCargoSecured()) {
        // done intaking
        // stop cargo motors
        m_cargoSubsystem->SetOff();
        // move lift up slightly to prevent cargo from coming out
        // m_liftSubsystem->SetCargoLiftLevel();
        // if (m_liftSubsystem->IsCargoIntakeLift()) {
        //     //set cargo wanted state
        //     return CargoNeutral;
        // } else {
        //     return CargoLift;
        // }
        // TODO: return a state
    } else {
        m_cargoSubsystem->SetIntake();
        // TODO: we want lift at the floor level
        // m_lif
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
