#include <Autonomous/Actions/PlaceHatchAction.h>
#include <Robot.h>
#include <CORERobotLib.h>

PlaceHatchAction::PlaceHatchAction(PlaceHatch i){
    m_PlaceHatchRequestedAction = i
}
void PlaceHatchAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus PlaceHatchAction::Action() {
    
    
    
    
    return COREAutonAction::actionStatus::END;


}

void PlaceHatchAction::ActionEnd() {

}
