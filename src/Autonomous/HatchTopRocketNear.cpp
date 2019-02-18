#include "HatchTopRocketNear.h"
#include <Robot.h>
#include "Actions.h"

HatchTopRocketNear::HatchTopRocketNear() :
	COREAuton("Drive Forward To Rocket") {
}

void HatchTopRocketNear::addNodes() {
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(),new RaiseLiftAction(ThirdLevelHatch));
    AddNext(m_placeHatchOnTopRocket);
    m_placeHatchOnTopRocket = new Node(5, new PlaceHatchAction());
    AddNext(m_lowerLiftToFirstLevel);
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelHatch));
}
