#include "HatchMidRocketNear.h"
#include <Robot.h>
#include "Actions.h"

HatchMidRocketNear::HatchMidRocketNear() :
	COREAuton("Hatch Middle Rocket Near Auton") {
}

void HatchMidRocketNear::AddNodes() {
    m_driveForwardToRocket = new Node(5, new DriveWaypointAction(), new RaiseLiftAction(SecondLevelHatch));
    m_placeHatchOnMidRocket = new Node(5, new PlaceHatchAction(CLOSE));
    m_lowerLiftToFirstLevel = new Node(5, new RaiseLiftAction(FirstLevelHatch));
    AddFirstNode(m_driveForwardToRocket);
    m_driveForwardToRocket->AddNext(m_placeHatchOnMidRocket);
    m_placeHatchOnMidRocket->AddNext(m_lowerLiftToFirstLevel);
}