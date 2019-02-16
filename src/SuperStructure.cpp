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
}

void SuperStructure::teleop() {
}

void SuperStructure::PostLoopTask() {
    SystemState newState = m_systemState;

    switch(m_systemState) {

        case SystemState::Transit:
            newState = handleTransit();
            break;

        case SystemState::TopRocketCargoScoring:
            newState = HandleTopRocketCargoScoring();
            break;

        case SystemState::MiddleRocketCargoScoring:
            newState = HandleMiddleRocketCargoScoring();
            break;

        case SystemState::BottomRocketCargoScoring:
            newState = HandleBottomRocketCargoScoring();
            break;

        case SystemState::TopRocketHatchScoring:
            newState = HandleTopRocketHatchScoring();
            break;

        case SystemState::MiddleRocketHatchScoring:
            newState = HandleMiddleRocketHatchScoring();
            break;

        case SystemState::BottomRocketHatchScoring:
            newState = HandleBottomRocketHatchScoring();
            break;

        case SystemState::CargoShipCargoScoring:
            newState = HandleCargoShipCargoScoring();
            break;

        case SystemState::CargoShipHatchScoring:
            newState = HandleCargoShipHatchScoring();

        case SystemState::FeederHatch:
            newState = HandleFeederHatch();
            break;
    }

    if(newState != m_systemState) {
        CORELog::logInfo("Changing states from " + to_string((int)m_systemState) + " to " + to_string((int)newState));
        m_systemState = newState;
    }

}

void SuperStructure::setWantedState(WantedState wantedState) {
    m_wantedState = wantedState;
}

SystemState SuperStructure::handleTransit() {
}

SystemState SuperStructure::HandleTopRocketCargoScoring() {
    //set lift to top rocket level
    m_liftSubsystem->SetThirdLevelCargoHeight();
    //spin cargo in reverse to eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelCargoHeight();
}

SystemState SuperStructure::HandleMiddleRocketCargoScoring() {
    //set lift to middle rocket level
    m_liftSubsystem->SetSecondLevelCargoHeight();
    //eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelCargoHeight();
}

SystemState SuperStructure::HandleBottomRocketCargoScoring() {
    //set lift to bottom rocket level
    m_liftSubsystem->SetFirstLevelCargoHeight();
    //eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    //Already There..
}

SystemState SuperStructure::HandleTopRocketHatchScoring() {
    //set lift to top rocket
    m_liftSubsystem->SetThirdLevelHatchHeight();
    //score the hatch
    m_hatchScorerSubsystem->TogglePunchHatch();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelHatchHeight();
}

SystemState SuperStructure::HandleMiddleRocketHatchScoring() {
    //set lift to middle rocket
    m_liftSubsystem->SetSecondLevelHatchHeight();
    //score the hatch
    m_hatchScorerSubsystem->TogglePunchHatch();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelHatchHeight();
}

SystemState	SuperStructure::HandleBottomRocketHatchScoring() {
    //set lift to bottom rocket
    m_liftSubsystem->SetFirstLevelHatchHeight();
    //score the hatch
    m_hatchScorerSubsystem->TogglePunchHatch();
    //set the lift to the default state
    //Already there
    
}

SystemState SuperStructure::HandleCargoShipCargoScoring() {
    //make sure the lift is at the correct hight [Set lift to correct height of cargo ship]
    m_liftSubsystem->SetCargoShipCargoLevel();
    //spin cargo intake in reverse to eject cargo into cargo ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
}

SystemState SuperStructure::HandleCargoShipHatchScoring() {
//make sure the lift is at the correct height [Set lift to correct height of cargo ship]
    m_liftSubsystem->SetCargoShipHatchLevel();
    m_hatchScorerSubsystem->ScoreHatchScorer();

}

SystemState SuperStructure::HandleFeederHatch() {
    //make sure the lift is in the right height
    m_liftSubsystem->SetFeederHeight();
    //score the hatch
    m_hatchScorerSubsystem->TogglePunchHatch();
    
}
