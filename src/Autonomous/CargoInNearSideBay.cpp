#include "CargoInNearSideBay.h"
#include <Robot.h>
#include "Actions.h"

CargoInNearSideBay::CargoInNearSideBay() :
	COREAuton("Hatch Near Cargo Ship Bay Auton") {
}

void CargoInNearSideBay::AddNodes() {
    m_driveForwardToNearSideCargoBay = new Node(5, new DriveWaypointAction());
    m_placeCargoInNearSideBay = new Node(5, new PlaceCargoAction(OUTTAKE));
    AddFirstNode(m_driveForwardToNearSideCargoBay);
    m_driveForwardToNearSideCargoBay->AddNext(m_placeCargoInNearSideBay);
}
