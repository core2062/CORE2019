#include "HatchTopRocketNear.h"
#include <Robot.h>
#include "Actions.h"

HatchTopRocketNear::HatchTopRocketNear() :
	COREAuton("Hatch Top Rocket Near Auton") {
}

void HatchTopRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(ThirdLevelHatch));
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelHatch));
    m_placeHatchOnTopRocket = new Node(5, new PlaceHatchAction(CLOSE));
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket->AddNext(m_placeHatchOnTopRocket);
    m_placeHatchOnTopRocket->AddNext(m_lowerLiftToFirstLevel);
}
