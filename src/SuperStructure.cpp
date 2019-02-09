#include <SuperStructure.h>

SuperStructure::SuperStructure() {

}

void SuperStructure::robotInit() {

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

        case SystemState::FeederCargo:
            newState = handleFeederCargo();
            break;
            
        case SystemState::FeederHatch:
            newState = handleFeederHatch();
            break;

            //e.
    }

}