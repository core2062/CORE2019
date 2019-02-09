#include <Autonomous/Actions/PlaceCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

PlaceCargoAction::PlaceCargoAction(){
    
}
void PlaceCargoAction::ActionInit(PlaceCargo i) {
    m_PlaceCargoRequestedAction = i;
}

CORE::COREAutonAction::actionStatus PlaceCargoAction::Action() {
    switch(m_PlaceCargoRequestedAction)
        case OUTTAKE:
            // Robot::GetInstance()->CargoSubsystem.SetOuttake()
    
    return COREAutonAction::actionStatus::END;


}

void PlaceCargoAction::ActionEnd() {

}
