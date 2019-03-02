#include "Autonomous/Actions/DriveDistanceAction.h"
#include "Robot.h"

DriveDistanceAction::DriveDistanceAction() {
}

void DriveDistanceAction::ActionInit() {

}

CORE::COREAutonAction::actionStatus DriveDistanceAction::Action() {
    if (Timer.Get() <= 3) {
        //Temporary Numbers should be changed to real ones  ->
		Robot::GetInstance()->driveSubsystem.SetMotorSpeed(0.4, 0.4);
		return COREAutonAction::actionStatus::CONTINUE;
	} else {
		return COREAutonAction::actionStatus::END;
	}
}

void DriveDistanceAction::ActionEnd() {
    Robot::GetInstance()->driveSubsystem.SetMotorSpeed(0,0);
}
