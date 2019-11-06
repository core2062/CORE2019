#include "WaypointTestAuton.h"
#include "Actions/DriveWaypointAction.h"
#include <frc/WPILib.h>

WaypointTestAuton::WaypointTestAuton() : COREAuton("Waypoint Follower Test Auton", true) {
}

void WaypointTestAuton::AddNodes() {
    m_driveForward = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    AddFirstNode(m_driveForward);
}