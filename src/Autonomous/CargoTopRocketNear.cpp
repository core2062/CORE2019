#include "CargoTopRocketNear.h"
#include "Robot.h"

CargoTopRocketNear::CargoTopRocketNear() :
	COREAuton("Cargo Top Rocket Near Auton") {
}

void CargoTopRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(ThirdLevelCargo));
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelHatch));
    m_placeCargoOnTopRocket = new Node(5, new PlaceCargoAction(OUTTAKE));
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket->AddNext(m_placeCargoOnTopRocket);
    m_placeCargoOnTopRocket->AddNext(m_lowerLiftToFirstLevel);
}
