#include "AutonNode.h"
#include "Robot.h"

SandstormAction::SandstormAction() {
}

void SandstormAction::ActionInit() {
	COREScheduler::teleopInit();
}

CORE::COREAutonAction::actionStatus SandstormAction::Action() {
    std::cout<< "This Auton Action Is Working"<<std::endl;
 	// COREScheduler::teleop();
	Robot::GetInstance()->hatchScorerSubsystem.teleop();
	Robot::GetInstance()->liftSubsystem.teleop();
	Robot::GetInstance()->driveSubsystem.teleop();
	Robot::GetInstance()->cargoSubsystem.teleop();
	return COREAutonAction::actionStatus::CONTINUE;
	//return COREAutonAction::actionStatus::END;
}

void SandstormAction::ActionEnd() {

}