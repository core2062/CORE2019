#include "CargoInNearSideBay.h"
#include <Autonomous/Actions.h>

CargoInNearSideBay::CargoInNearSideBay() :
	COREAuton("Cargo Near Cargo Ship Bay Auton") {
}

void CargoInNearSideBay::AddNodes() {
    m_driveForwardToNearSideCargoBay = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(FirstLevelCargo));
    m_placeCargoInNearSideBay = new Node(5, new PlaceCargoAction(PlaceCargo::OUTTAKE_CARGO));
    AddFirstNode(m_driveForwardToNearSideCargoBay);
    m_driveForwardToNearSideCargoBay->AddNext(m_liftLiftToCargoBayPosition);
    m_liftLiftToCargoBayPosition->AddNext(m_placeCargoInNearSideBay);
}
