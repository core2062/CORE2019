#include "CargoNearAndMidSideBay.h"
#include <Robot.h>
#include <CORERobotLib.h>

CargoNearAndMidSideBay::CargoNearAndMidSideBay() :
	COREAuton("Cargo Near And Mid Side Bay") {
}

void CargoNearAndMidSideBay::AddNodes() {
    m_driveToNearSideBay = new Node(10, new DriveWaypointAction(), new RaiseLiftAction(SecondLevelCargo));
    m_placeCargoInNearSideBay = new Node(10, new PlaceCargoAction(OUTTAKE));
    m_driveToCargoDepot = new Node(10, new DriveWaypointAction(), new RaiseLiftAction(FirstLevelHatch));
    m_grabCargoFromCargoDepot = new Node(10, new GrabCargoAction());
    m_driveToMidSideBay = new Node(10, new DriveWaypointAction(), new RaiseLiftAction(SecondLevelCargo));
    m_placeCargoInMidSideBay = new Node(10, new PlaceCargoAction(OUTTAKE));
    AddFirstNode(m_driveToNearSideBay);
    m_driveToNearSideBay->AddNext(m_placeCargoInNearSideBay);
    m_placeCargoInNearSideBay->AddNext(m_driveToCargoDepot);
    m_driveToCargoDepot->AddNext(m_grabCargoFromCargoDepot);
    m_grabCargoFromCargoDepot->AddNext(m_driveToMidSideBay);
    m_driveToMidSideBay->AddNext(m_placeCargoInMidSideBay);
}
