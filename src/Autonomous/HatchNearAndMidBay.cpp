#include "HatchNearAndMidBay.h"
#include <Robot.h>

HatchNearAndMidBay::HatchNearAndMidBay() :
	COREAuton("Hatch Near Cargoship Middle Bay Auton") {
}

void HatchNearAndMidBay::AddNodes() {
    m_driveForwardFirstBaySideCargoShip = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_placeHatchOnNearSideBay = new Node(5, new PlaceHatchAction(CLOSE));
    m_driveToPlayerStation = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_grabHatchFromPlayerStation = new Node(5, new GrabHatchAction(PUSH));
    m_driveToMidSideCargoBay = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_placeHatchOnMidSideCargoBay = new Node(5, new PlaceHatchAction(CLOSE));
    m_placeHatchOnNearSideBay->AddNext(m_driveToPlayerStation);
    AddFirstNode(m_driveForwardFirstBaySideCargoShip);
    m_driveForwardFirstBaySideCargoShip->AddNext(m_placeHatchOnNearSideBay);
    m_driveToPlayerStation->AddNext(m_grabHatchFromPlayerStation);
    m_grabHatchFromPlayerStation->AddNext(m_driveToMidSideCargoBay);
    m_driveToMidSideCargoBay->AddNext(m_placeHatchOnMidSideCargoBay);

}