#include <Autonomous/Actions.h>
#include <Robot.h>
#include <frc/WPILib.h>
#include "LeftToRocketHatchAuton.h"

LeftToRocketHatchAuton::LeftToRocketHatchAuton() : COREAuton("One hatch, left starting, rocket") {
}

void LeftToRocketHatchAuton::AddNodes() {
    m_driveToRocket = new Node(10, new DriveWaypointAction(TankPath::FromFile("leftStartingToRocketHatch.json", false)));
    m_placeHatch = new Node(5, new PlaceHatchAction(PlaceHatch::EXTEND));
    AddFirstNode(m_driveToRocket);
    m_driveToRocket->AddNext(m_placeHatch);
}