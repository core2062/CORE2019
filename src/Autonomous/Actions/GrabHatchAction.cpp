#include <Autonomous/Actions/GrabHatchAction.h>
#include <Robot.h>

GrabHatchAction::GrabHatchAction(GrabHatch Action){
    m_grabHatchRequestedAction = Action;
}

void GrabHatchAction::ActionInit(){
    switch(m_grabHatchRequestedAction){
        case OPEN:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
        case CLOSE:
           // Robot::GetInstance()->hatchScorerSubsystem.CloseClaw();
            break;
        case PUSH: 
            Robot::GetInstance()->hatchScorerSubsystem.PunchHatch();
        break;
    }
}

CORE::COREAutonAction::actionStatus GrabHatchAction::Action() {
    return COREAutonAction::actionStatus::END;
}

void GrabHatchAction::ActionEnd() {
}
