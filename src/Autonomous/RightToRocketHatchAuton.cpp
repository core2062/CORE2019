// #include <Autonomous/Actions.h>
// #include <Robot.h>
// #include <frc/WPILib.h>
// #include "RightToRocketHatchAuton.h"

// RightToRocketHatchAuton::RightToRocketHatchAuton() : COREAuton("One hatch, right starting, rocket") {
// }

// void RightToRocketHatchAuton::AddNodes() {
//     m_driveToRocket = new Node(10, new DriveWaypointAction(TankPath::FromFile("rightStartingToRocketHatch.json", false)));
//     m_placeHatch = new Node(5, new PlaceHatchAction(PlaceHatch::EXTEND));
//     AddFirstNode(m_driveToRocket);
//     m_driveToRocket->AddNext(m_placeHatch);
// }