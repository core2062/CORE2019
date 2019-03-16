#include "HatchTopRocketNear.h"
#include <Robot.h>
#include "Actions.h"

HatchTopRocketNear::HatchTopRocketNear() :
	COREAuton("Hatch Top Rocket Near Auton") {
}

void HatchTopRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(TankPath::FromFile("path.json", false)), new RaiseLiftAction(RaiseLift::ThirdLevelHatch)
        , new PlaceHatchAction(PlaceHatch::EXTEND));
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(RaiseLift::FirstLevelHatch));
    m_placeHatchOnTopRocket = new Node(5, new PlaceHatchAction(PlaceHatch::CLOSE));
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket->AddNext(m_placeHatchOnTopRocket);
    m_placeHatchOnTopRocket->AddNext(m_lowerLiftToFirstLevel);
}
