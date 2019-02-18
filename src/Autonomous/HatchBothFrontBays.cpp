#include "HatchBothFrontBays.h"
#include <Robot.h>

HatchBothFrontBays::HatchBothFrontBays() :
	COREAuton("Drive Forward to Cargo Bay and Place Hatch") {
}

void HatchBothFrontBays::addNodes() {
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction());
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction());
}