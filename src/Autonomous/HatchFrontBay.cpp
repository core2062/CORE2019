#include "HatchFrontBay.h"
#include <Robot.h>

HatchFrontBay::HatchFrontBay() :
	COREAuton("Hatch Front Bay") {
}

void HatchFrontBay::AddNodes() {
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction());
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction(CLOSE));
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_driveForwardToFrontCargoBay->AddNext(m_placeHatchOnFrontCargoBay);
}