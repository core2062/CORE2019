#include "Autonomous/Actions/GrabCargoAction.h"
#include "Robot.h"

GrabCargoAction::GrabCargoAction(GrabCargo Action){
    m_grabCargoRequestedAction = Action;
}
void GrabCargoAction::ActionInit() {
    
}

CORE::COREAutonAction::actionStatus GrabCargoAction::Action() {
    switch(m_grabCargoRequestedAction){
        case GrabCargo::INTAKE:
            Robot::GetInstance()->cargoSubsystem.SetIntake();
        case GrabCargo::OUTTAKE:
            Robot::GetInstance()->cargoSubsystem.SetOuttake();
            break;
        default:
            //Robot::GetInstance()->cargoSubsystem.SetOff();
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void GrabCargoAction::ActionEnd() {
}
