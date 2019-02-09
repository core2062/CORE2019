#include <Robot.h>

#include <Autonomous/Actions/DriveWaypointAction.h>

DriveWaypointAction::DriveWaypointAction(){
    
}
void DriveWaypointAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus DriveWaypointAction::Action() {
    return COREAutonAction::actionStatus::END;
}

void DriveWaypointAction::ActionEnd() {

}
