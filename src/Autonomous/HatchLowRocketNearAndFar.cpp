

#include "HatchLowRocketNearAndFar.h"
#include "Robot.h"
#include <CORERobotLib.h>

HatchLowRocketNearAndFar::HatchLowRocketNearAndFar() :
	COREAuton("Hatch Low Rocket Near And Far") {
}

void HatchLowRocketNearAndFar::AddNodes() {
    m_driveLowRocketNearSide = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_placeHatchOnLowNearSideRocket = new Node(10, new PlaceHatchAction(CLOSE));
    m_driveToPlayerStation = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_grabHatchFromPlayerStation = new Node(10, new GrabHatchAction(PUSH));
    m_driveToFarSideRocket = new Node(10, new DriveWaypointAction(TankPath::FromFile("path.json", false)));
    m_placeHatchOnFarSideRocket = new Node(10, new PlaceHatchAction(CLOSE));
    AddFirstNode(m_driveLowRocketNearSide);
    m_driveLowRocketNearSide->AddNext(m_placeHatchOnLowNearSideRocket);
    m_placeHatchOnLowNearSideRocket->AddNext(m_driveToPlayerStation);
    m_driveToPlayerStation->AddNext(m_grabHatchFromPlayerStation);
    m_grabHatchFromPlayerStation->AddNext(m_driveToFarSideRocket);
    m_driveToFarSideRocket->AddNext(m_placeHatchOnFarSideRocket);
}
