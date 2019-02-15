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
            newState = handleTopRocketCargoScoring();
            break;

        case SystemState::MiddleRocketCargoScoring:
            newState = handleMiddleRocketCargoScoring();
            break;

        case SystemState::BottomRocketCargoScoring:
            newState = handleBottemRocketCargoScoring();
            break;

        case SystemState::TopRocketHatchScoring:
            newState = handleTopRocketHatchScoring();
            break;

        case SystemState::MiddleRocketHatchScoring:
            newState = handleMiddleRocketHatchScoring();
            break;

        case SystemState::BottomRocketHatchScoring:
            newState = handleBottemRocketHatchScoring();
            break;

        case SystemState::CargoShipCargoScoring:
            newState = handleCargoShipCargoScoring();
            break;

        case SystemState::FeederHatch:
            newState = handleFeederHatch();
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

SystemState SuperStructure::handleTopRocketCargoScoring() {
    //set lift to top rocket level
    m_liftSubsystem->SetThirdLevelCargoHeight();
    //spin cargo in reverse to eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelCargoHeight();
}

SystemState SuperStructure::handleMiddleRocketCargoScoring() {
    //set lift to middle rocket level
    m_liftSubsystem->SetSecondLevelCargoHeight();
    //eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    m_liftSubsystem->SetFirstLevelCargoHeight();
}

SystemState SuperStructure::handleBottemRocketCargoScoring() {
    //set lift to bottom rocket level
    m_liftSubsystem->SetFirstLevelCargoHeight();
    //eject cargo into rocket ship
    m_cargoSubsystem->SetOuttake();
    //set the lift to the default state
    //Already There..
}

SystemState SuperStructure::handleTopRocketHatchScoring() {
    //set lift to top rocket
    m_liftSubsystem->SetThirdLevelHatchHeight();
    //single function
        //{extend hatch scorer
        m_hatchScorerSubsystem->
        //open hatch scorer
        //punch hatch scorer
        //close hatch scorer
        //retract hatch scorer}
    //set the lift to the default state
}

SystemState SuperStructure::handleMiddleRocketHatchScoring() {
    //set lift to middle rocket
    //single function
        //{extend hatch scorer
        //open hatch scorer
        //punch hatch scorer
        //close hatch scorer
        //retract hatch scorer}
    //set the lift to the default state
}

SystemState	SuperStructure::handleBottemRocketHatchScoring() {
    //set lift to bottom rocket
    //single function
        //{extend hatch scorer
        //open hatch scorer
        //punch hatch scorer
        //close hatch scorer
        //retract hatch scorer}
    //set the lift to the default state
}

SystemState SuperStructure::handleCargoShipCargoScoring() {
    //make sure the lift is at the correct hight [Set lift to correct height of cargo ship]
    //spin cargo intake in reverse to eject cargo into cargo ship
    //set the lift to the default state
}

SystemState SuperStructure::handleFeederHatch() {
    //make sure the lift is in the right height
    //close hatch scorer
    //extend hatch scorer
    //open hatch scorer
    //retract hatch scorer
}
