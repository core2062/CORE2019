#include <Autonomous/Actions/PlaceCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

PlaceCargoAction::PlaceCargoAction(){
    
}
void PlaceCargoAction::ActionInit(PlaceCargo Action) {
    m_PlaceCargoRequestedAction = Action;
}

CORE::COREAutonAction::actionStatus PlaceCargoAction::Action() {
    switch(m_PlaceCargoRequestedAction)
        case OUTTAKE:
            Robot::GetInstance()->cargoSubsystem.SetOuttake();
    
    return COREAutonAction::actionStatus::END;


}

void PlaceCargoAction::ActionEnd() {

}
