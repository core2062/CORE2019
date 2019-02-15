#include <Autonomous/Actions/GrabCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabCargoAction::GrabCargoAction(){
    
}
void GrabCargoAction::ActionInit(GrabCargo Action) {
    m_GrabCargoRequestedAction = Action;
}

CORE::COREAutonAction::actionStatus GrabCargoAction::Action() {
    switch(m_GrabCargoRequestedAction){
        case INTAKE:
            Robot::GetInstance()->cargoSubsystem.SetIntake();
    }
    
    return COREAutonAction::actionStatus::END;


}

void GrabCargoAction::ActionEnd() {

}
