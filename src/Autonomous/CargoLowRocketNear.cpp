#include "CargoLowRocketNear.h"
#include <Robot.h>
#include <CORERobotLib.h>

CargoLowRocketNear::CargoLowRocketNear() :
	COREAuton("Cargo Low Rocket Near") {
}

void CargoLowRocketNear::AddNodes() {
    m_driveLowRocketNearSide = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(FirstLevelCargo));
    m_placeCargoOnLowNearSide = new Node(10, new PlaceCargoAction(PlaceCargo::OUTTAKE_CARGO));
    AddFirstNode(m_driveLowRocketNearSide);
    m_driveLowRocketNearSide->AddNext(m_raiseLiftLowRocket);
    m_raiseLiftLowRocket->AddNext(m_placeCargoOnLowNearSide);
}
