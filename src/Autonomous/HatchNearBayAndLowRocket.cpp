#include "HatchNearBayAndLowRocket.h"
#include <Robot.h>

HatchNearBayAndLowRocket::HatchNearBayAndLowRocket() :
	COREAuton("Near Hatch and Low Rocket Auton") {
}

void HatchNearBayAndLowRocket::AddNodes() {
    m_driveForwardFirstBaySideCargoShip = new Node(5, new DriveWaypointAction());
    m_placeHatchOnLowRocket = new Node(5, new PlaceHatchAction(CLOSE));
    m_placeHatchOnNearSideBay = new Node(5, new PlaceHatchAction(CLOSE));
    m_driveToPlayerStation = new Node(5, new DriveWaypointAction());
    m_grabHatchFromPlayerStation = new Node(5, new GrabHatchAction(PUSH));
    m_driveToLowNearRocket = new Node(5, new DriveWaypointAction());
    AddFirstNode(m_driveForwardFirstBaySideCargoShip);
    m_driveForwardFirstBaySideCargoShip->AddNext(m_placeHatchOnNearSideBay);
    m_placeHatchOnNearSideBay->AddNext(m_driveToPlayerStation);
    m_driveToPlayerStation->AddNext(m_grabHatchFromPlayerStation);
    m_grabHatchFromPlayerStation->AddNext(m_driveToLowNearRocket);
    m_driveToLowNearRocket->AddNext(m_placeHatchOnLowRocket);


}