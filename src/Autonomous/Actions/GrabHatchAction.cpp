#include <Autonomous/Actions/GrabHatchAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabHatchAction::GrabHatchAction(GrabHatch i){
    m_GrabHatchRequestedAction = i;
}

void GrabHatchAction::ActionInit(){
    switch(m_GrabHatchRequestedAction){
        case OPEN:
            // Robot::GetInstance()->HatchScorerSubsystem.ToggleClaw();
            break;
        case EXTEND: 
            // Robot::GetInstance()->HatchSorerSubsystem.PunchHatch();
        ;
    }
}

CORE::COREAutonAction::actionStatus GrabHatchAction::Action() {
    return COREAutonAction::actionStatus::END;


}

void GrabHatchAction::ActionEnd() {

}
