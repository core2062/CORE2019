#include "TeleopAction.h"
#include "Robot.h"

TeleopAction::TeleopAction() {
}

void TeleopAction::ActionInit() {
	COREScheduler::teleopInit();
}

CORE::COREAutonAction::actionStatus TeleopAction::Action() {
	// Robot::GetInstance()->hatchScorerSubsystem.teleop();
	// Robot::GetInstance()->liftSubsystem.teleop();
	Robot::GetInstance()->driveSubsystem.teleop();
	//Robot::GetInstance()->cargoSubsystem.teleop();
	return COREAutonAction::actionStatus::CONTINUE;
}

void TeleopAction::ActionEnd() {

}