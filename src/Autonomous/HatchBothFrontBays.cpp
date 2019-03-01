#include "HatchBothFrontBays.h"
#include <Robot.h>
#include <CORERobotLib.h>

HatchBothFrontBays::HatchBothFrontBays() :
	COREAuton("Hatch Both Front Bays") {
}

void HatchBothFrontBays::AddNodes() {
    m_driveForwardToPlayerStation = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction(CLOSE));
    m_placeHatchOnOtherFrontCargoBay = new Node(10, new PlaceHatchAction(CLOSE));
    m_driveForwardToOtherFrontCargoBay = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_grabHatchFromPlayerStation = new Node(10, new GrabHatchAction(PUSH));
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_driveForwardToFrontCargoBay->AddNext(m_placeHatchOnFrontCargoBay);
    m_placeHatchOnFrontCargoBay->AddNext(m_driveForwardToPlayerStation);
    m_driveForwardToPlayerStation->AddNext(m_grabHatchFromPlayerStation);
    m_driveForwardToOtherFrontCargoBay->AddNext(m_placeHatchOnOtherFrontCargoBay);
    m_grabHatchFromPlayerStation->AddNext(m_driveForwardToOtherFrontCargoBay);
    
}