#include "HatchNearBay.h"
#include <Robot.h>
#include "Actions.h"

HatchNearBay::HatchNearBay() :
	COREAuton("Hatch Near Cargoship Bay Auton") {
}

void HatchNearBay::AddNodes() {
    m_driveForwardToNearSideCargoBay = new Node(5, new DriveWaypointAction());
    m_placeHatchOnNearSideBay = new Node(5, new PlaceHatchAction(CLOSE));
    AddFirstNode(m_driveForwardToNearSideCargoBay);
    m_driveForwardToNearSideCargoBay->AddNext(m_placeHatchOnNearSideBay);
}
