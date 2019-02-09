#include <Autonomous/Actions/RaiseLiftAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

RaiseLiftAction::RaiseLiftAction(){
    
}
void RaiseLiftAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus RaiseLiftAction::Action() {
    return COREAutonAction::actionStatus::END;


}

void RaiseLiftAction::ActionEnd() {

}
