#include <Autonomous/Actions/PlaceHatchAction.h>
#include <Robot.h>

PlaceHatchAction::PlaceHatchAction(PlaceHatch Action){
    m_placeHatchRequestedAction = Action;
}
void PlaceHatchAction::ActionInit() {

}

CORE::COREAutonAction::actionStatus PlaceHatchAction::Action() {
    switch(m_placeHatchRequestedAction){
        case CLOSE:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
            break;
        case EXTEND:
            Robot::GetInstance()->hatchScorerSubsystem.ScoreHatch();
        break;
    } 
    return COREAutonAction::actionStatus::END;
}

void PlaceHatchAction::ActionEnd() {

}
