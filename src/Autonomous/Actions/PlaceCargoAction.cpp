#include <Autonomous/Actions/PlaceCargoAction.h>
#include <Robot.h>

PlaceCargoAction::PlaceCargoAction(PlaceCargo Action){
    m_placeCargoRequestedAction = Action;
}
void PlaceCargoAction::ActionInit() {
    
}

CORE::COREAutonAction::actionStatus PlaceCargoAction::Action() {
    switch(m_placeCargoRequestedAction) {
        case PlaceCargo::OUTTAKE:
            Robot::GetInstance()->cargoSubsystem.SetOuttake();
        break;
    }
    return COREAutonAction::actionStatus::END;
}

void PlaceCargoAction::ActionEnd() {

}

