#include <Autonomous/Actions/GrabCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabCargoAction::GrabCargoAction(){
    
}
void GrabCargoAction::ActionInit(GrabCargo Action) {
    m_grabCargoRequestedAction = Action;
}

CORE::COREAutonAction::actionStatus GrabCargoAction::Action() {
    switch(m_grabCargoRequestedAction){
        case INTAKE:
            Robot::GetInstance()->cargoSubsystem.SetIntake();
    }
    
    return COREAutonAction::actionStatus::END;


}

void GrabCargoAction::ActionEnd() {

}
