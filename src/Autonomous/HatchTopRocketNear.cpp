#include "HatchTopRocketNear.h"
#include <Robot.h>
#include "Actions.h"

HatchTopRocketNear::HatchTopRocketNear() :
	COREAuton("Drive Forward To Rocket") {
}

void HatchTopRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(), new RaiseLiftAction(ThirdLevelHatch));
    AddFirstNode(m_driveForwardToRocket);
    m_placeHatchOnTopRocket = new Node(5, new PlaceHatchAction(CLOSE));
    m_placeHatchOnTopRocket->AddNext(m_placeHatchOnTopRocket);
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelHatch));
    m_lowerLiftToFirstLevel->AddNext(m_lowerLiftToFirstLevel);
}
