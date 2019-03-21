// #include <Autonomous/Actions.h>
// #include <Robot.h>
// #include <frc/WPILib.h>
// #include "OneHatchCargoShipToFeederAuton.h"

// OneHatchCargoShipToFeederAuton::OneHatchCargoShipToFeederAuton() : 
//     COREAuton("One hatch, center starting, cargo ship, to feeder") {
// }

// void OneHatchCargoShipToFeederAuton::AddNodes() {
//     m_driveToCargoShip = new Node(7, new DriveWaypointAction(TankPath::FromFile("centerToRightCargoShip.json", false)));
//     m_placeHatch = new Node(3, new PlaceHatchAction(PlaceHatch::EXTEND));
//     m_driveCargoShipToFeeder = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
//     // Need to add the actual file for this
//     AddFirstNode(m_driveToCargoShip);
//     m_driveToCargoShip->AddNext(m_placeHatch);
//     m_placeHatch->AddNext(m_driveCargoShipToFeeder);
// }