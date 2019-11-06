#include <Robot.h>
#include <Autonomous/Actions/DriveWaypointAction.h>

DriveWaypointAction::DriveWaypointAction(TankPath path){
    m_path = std::move(path);
    m_reversed = false;
    m_tolerance = 0.25;
    m_maxAccel = 40;
    m_gradualStop = true;
    m_lookahead = 24.0;
}
void DriveWaypointAction::ActionInit() {
    Robot::GetInstance()->driveSubsystem.FollowPath(m_path, m_reversed, m_maxAccel, m_gradualStop, m_lookahead);
}

CORE::COREAutonAction::actionStatus DriveWaypointAction::Action() {
    SmartDashboard::PutNumber("Gyro Yaw", Robot::GetInstance()->driveSubsystem.GetYaw());
    if (!Robot::GetInstance()->driveSubsystem.PathDone()) {
        SmartDashboard::PutNumber("Gyro Yaw", Robot::GetInstance()->driveSubsystem.GetYaw());
        return COREAutonAction::actionStatus::CONTINUE;
    }
    SmartDashboard::PutNumber("Gyro Yaw", Robot::GetInstance()->driveSubsystem.GetYaw());
    return COREAutonAction::actionStatus::END;
}

void DriveWaypointAction::ActionEnd() {

}
