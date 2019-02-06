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

        case TopRocketHatchScoring:
            newState = handleTopRocketHatchScoring();
            break;

        case MiddleRocketHatchScoring:
            newState = handleMiddleRocketHatchScoring();
            break;

        case BottomRocketHatchScoring:
            newState = handleBottemRocketHatchScoring();
            break;

        case CargoShipCargoScoring:
            newState = handleCargoShipCargoScoring();
            break;

        case FeederCargo:
            newState = handleFeederCargo();
            break;
        case FeederHatch:
            newState = handleFeederHatch();
            break;
    }

}