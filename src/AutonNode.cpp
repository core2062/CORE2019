#include "AutonNode.h"

SandstormAction::SandstormAction() {
}

void SandstormAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus SandstormAction::Action() {
    std::cout<< "This Auton Action Is Working"<<std::endl;
	//return COREAutonAction::actionStatus::CONTINUE;
	return COREAutonAction::actionStatus::END;
}

void SandstormAction::ActionEnd() {

}