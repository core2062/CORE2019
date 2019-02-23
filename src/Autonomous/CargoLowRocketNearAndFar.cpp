#include "CargoLowRocketNearAndFar.h"
#include <Robot.h>
#include <CORERobotLib.h>

CargoLowRocketNearAndFar::CargoLowRocketNearAndFar() :
	COREAuton("Cargo Low Rocket Near And Far") {
}

void CargoLowRocketNearAndFar::AddNodes() {
    m_driveLowRocketNearSide = new Node(10, new DriveWaypointAction(), new RaiseLiftAction(FirstLevelCargo));
    m_placeCargoOnLowNearSideRocket = new Node(10, new PlaceCargoAction(OUTTAKE));
    m_driveToPlayerStation = new Node(10, new DriveWaypointAction());
    m_grabCargoFromPlayerStation = new Node(10, new GrabCargoAction(INTAKE));
    m_driveToFarSideRocket = new Node(10, new DriveWaypointAction());
    m_placeCargoOnFarSideRocket = new Node(10, new PlaceCargoAction(OUTTAKE));
    AddFirstNode(m_driveLowRocketNearSide);
    m_driveLowRocketNearSide->AddNext(m_placeCargoOnLowNearSideRocket);
    m_placeCargoOnLowNearSideRocket->AddNext(m_driveToPlayerStation);
    m_driveToPlayerStation->AddNext(m_grabCargoFromPlayerStation);
    m_grabCargoFromPlayerStation->AddNext(m_driveToFarSideRocket);
    m_driveToFarSideRocket->AddNext(m_placeCargoOnFarSideRocket);
}
