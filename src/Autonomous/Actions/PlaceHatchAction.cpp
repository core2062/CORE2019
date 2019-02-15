#include <Autonomous/Actions/PlaceHatchAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

PlaceHatchAction::PlaceHatchAction(PlaceHatch Action){
    m_PlaceHatchRequestedAction = Action;
}
void PlaceHatchAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus PlaceHatchAction::Action() {
    switch(m_PlaceHatchRequestedAction){
        case CLOSE:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
            break;
        case EXTEND:
            Robot::GetInstance()->hatchScorerSubsystem.PunchHatch();
    }
    
    
    return COREAutonAction::actionStatus::END;


}

void PlaceHatchAction::ActionEnd() {

}
