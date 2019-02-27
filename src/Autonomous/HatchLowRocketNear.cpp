#include "HatchLowRocketNear.h"
#include <Robot.h>
#include <CORERobotLib.h>

HatchLowRocketNear::HatchLowRocketNear() :
	COREAuton("Hatch Low Rocket Near") {
}

void HatchLowRocketNear::AddNodes() {
    m_driveLowRocketNearSide = new Node(10, new DriveWaypointAction());
    m_placeHatchOnLowNearSide = new Node(10, new PlaceHatchAction(CLOSE));
    AddFirstNode(m_driveLowRocketNearSide);
    m_driveLowRocketNearSide->AddNext(m_placeHatchOnLowNearSide);
}
