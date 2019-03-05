#include "Autonomous/Actions/PlaceHatchAction.h"
#include "Robot.h"

PlaceHatchAction::PlaceHatchAction(PlaceHatch Action){
    m_placeHatchRequestedAction = Action;
}

void PlaceHatchAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus PlaceHatchAction::Action() {
    switch(m_placeHatchRequestedAction){
        case PlaceHatch::CLOSE:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
            break;
        case PlaceHatch::EXTEND:
            Robot::GetInstance()->hatchScorerSubsystem.PunchHatch();
        break;
    } 
    return COREAutonAction::actionStatus::END;
}

void PlaceHatchAction::ActionEnd() {
}
