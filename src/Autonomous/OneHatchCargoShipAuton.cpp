// #include <Autonomous/Actions.h>
// #include <Robot.h>
// #include <frc/WPILib.h>
// #include "OneHatchCargoShipAuton.h"

// OneHatchCargoShipAuton::OneHatchCargoShipAuton() : COREAuton("One hatch, center starting, cargo ship") {
// }

// void OneHatchCargoShipAuton::AddNodes() {
//     m_driveToCargoShip = new Node(10, new DriveWaypointAction(TankPath::FromFile("centerToRightCargoShip.json", false)));
//     m_placeHatch = new Node(5, new PlaceHatchAction(PlaceHatch::EXTEND));
//     AddFirstNode(m_driveToCargoShip);
//     m_driveToCargoShip->AddNext(m_placeHatch);
// }