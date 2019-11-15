#include "WaypointTestAuton.h"
#include "Actions/DriveWaypointAction.h"
#include <frc/WPILib.h>

WaypointTestAuton::WaypointTestAuton() : COREAuton("Waypoint Follower Test Auton", true) {
}

void WaypointTestAuton::AddNodes() {
    tankPath = TankPath::FromFile("path.json", false);
    m_driveForward = new Node(5, new DriveWaypointAction(&tankPath));
    AddFirstNode(m_driveForward);
} //Pointers instead of what we currently have 