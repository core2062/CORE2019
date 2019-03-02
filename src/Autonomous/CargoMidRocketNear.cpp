#include "CargoMidRocketNear.h"
#include <Robot.h>
#include "Actions.h"

CargoMidRocketNear::CargoMidRocketNear() :
	COREAuton("Cargo Middle Rocket Near Auton") {
}

void CargoMidRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(SecondLevelCargo));
    m_placeCargoOnMidRocket = new Node(5, new PlaceCargoAction(OUTTAKE));
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelCargo));
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket->AddNext(m_placeCargoOnMidRocket);
    m_placeCargoOnMidRocket->AddNext(m_lowerLiftToFirstLevel);
}
