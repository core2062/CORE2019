#include "WaypointTestAuton.h"
#include <Autonomous/Actions.h>

WaypointTestAuton::WaypointTestAuton() :
	COREAuton("Waypoint Follower Test Auton") {
}

void WaypointTestAuton::AddNodes() {
    m_driveForward = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    AddFirstNode(m_driveForward);
}