#include <Autonomous/Actions/GrabCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

GrabCargoAction::GrabCargoAction(){
    
}
void GrabCargoAction::ActionInit(GrabCargo i) {
    m_GrabCargoRequestedAction = i;
}

CORE::COREAutonAction::actionStatus GrabCargoAction::Action() {
    switch(m_GrabCargoRequestedAction)
        case INTAKE:
            // Robot::GetInstance()->CargoSubsystem.SetIntake()
    
    return COREAutonAction::actionStatus::END;


}

void GrabCargoAction::ActionEnd() {

}
