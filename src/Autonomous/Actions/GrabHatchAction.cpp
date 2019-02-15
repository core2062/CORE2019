#include <Autonomous/Actions/GrabHatchAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabHatchAction::GrabHatchAction(GrabHatch Action){
    m_GrabHatchRequestedAction = Action;
}

void GrabHatchAction::ActionInit(){
    switch(m_GrabHatchRequestedAction){
        case OPEN:
            Robot::GetInstance()->hatchScorerSubsystem.ToggleClaw();
            break;
        case EXTEND: 
            Robot::GetInstance()->hatchScorerSubsystem.PunchHatch();
    
    }
}

CORE::COREAutonAction::actionStatus GrabHatchAction::Action() {
    return COREAutonAction::actionStatus::END;


}

void GrabHatchAction::ActionEnd() {

}
