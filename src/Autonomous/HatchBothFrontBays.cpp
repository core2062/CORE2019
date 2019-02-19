#include "HatchBothFrontBays.h"
#include <Robot.h>
#include <CORERobotLib.h>

HatchBothFrontBays::HatchBothFrontBays() :
	COREAuton("Drive Forward to Cargo Bay and Place Hatch") {
}

void HatchBothFrontBays::AddNodes() {
    m_driveForwardToFrontCargoBay = new Node(10, new DriveWaypointAction());
    AddFirstNode(m_driveForwardToFrontCargoBay);
    m_placeHatchOnFrontCargoBay = new Node(10, new PlaceHatchAction(CLOSE));
    m_driveForwardToFrontCargoBay->AddNext(m_placeHatchOnFrontCargoBay);
}