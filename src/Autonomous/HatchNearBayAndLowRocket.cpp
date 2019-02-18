#include "HatchNearBayAndLowRocket.h"
#include <Robot.h>

HatchNearBayAndLowRocket::HatchNearBayAndLowRocket() :
	COREAuton("Drive Forward No Encoders") {
}

void HatchNearBayAndLowRocket::addNodes() {
    AddFirstNode(m_moveForward);
    m_moveForward = new Node(5, new DriveDistanceAction());
}