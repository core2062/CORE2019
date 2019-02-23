#include "CargoLowRocketNear.h"
#include <Robot.h>
#include <CORERobotLib.h>

CargoLowRocketNear::CargoLowRocketNear() :
	COREAuton("Cargo Low Rocket Near") {
}

void CargoLowRocketNear::AddNodes() {
    m_driveLowRocketNearSide = new Node(10, new DriveWaypointAction());
    m_raiseLiftLowRocket = new Node(10, new RaiseLiftAction(FirstLevelCargo));
    m_placeCargoOnLowNearSide = new Node(10, new PlaceCargoAction(OUTTAKE));
    AddFirstNode(m_driveLowRocketNearSide);
    m_driveLowRocketNearSide->AddNext(m_raiseLiftLowRocket);
    m_raiseLiftLowRocket->AddNext(m_placeCargoOnLowNearSide);
}
