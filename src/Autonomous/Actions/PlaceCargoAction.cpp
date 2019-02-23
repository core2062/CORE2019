#include <Autonomous/Actions/PlaceCargoAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

PlaceCargoAction::PlaceCargoAction(PlaceCargo Action){
    m_placeCargoRequestedAction = Action;
}
void PlaceCargoAction::ActionInit() {
    
}

CORE::COREAutonAction::actionStatus PlaceCargoAction::Action() {
    switch(m_placeCargoRequestedAction)
        case OUTTAKE:
            Robot::GetInstance()->cargoSubsystem.SetOuttake();
    
    return COREAutonAction::actionStatus::END;


}

void PlaceCargoAction::ActionEnd() {

}

