#include <Autonomous/Actions/GrabHatchAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabHatchAction::GrabHatchAction(GrabHatch Action){
    m_grabHatchRequestedAction = Action;
}

void GrabHatchAction::ActionInit(){
    switch(m_grabHatchRequestedAction){
        case OPEN:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
            break;
        case PUSH: 
            Robot::GetInstance()->hatchScorerSubsystem.PunchHatch();
    
    }
}

CORE::COREAutonAction::actionStatus GrabHatchAction::Action() {
    return COREAutonAction::actionStatus::END;


}

void GrabHatchAction::ActionEnd() {

}
