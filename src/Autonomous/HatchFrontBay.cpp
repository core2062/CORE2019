#include "HatchFrontBay.h"
#include <Robot.h>

HatchFrontBay::HatchFrontBay() :
	COREAuton("Drive Forward to Cargo Bay and Place Hatch") {
}

void HatchFrontBay::AddNodes() {
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction());
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction(CLOSE));
    m_driveForwardToFrontCargoBay->AddNext(m_placeHatchOnFrontCargoBay);
}