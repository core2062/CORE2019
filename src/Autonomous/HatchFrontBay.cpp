#include "HatchBothFrontBays.h"
#include <Robot.h>

HatchFrontBay::HatchFrontBay() :
	COREAuton("Drive Forward to Cargo Bay and Place Hatch") {
}

void HatchFrontBay::addNodes() {
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction());
    AddNext(m_placeHatchOnFrontCargoBay);
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction());
}