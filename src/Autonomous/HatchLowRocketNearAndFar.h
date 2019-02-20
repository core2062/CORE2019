#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchLowRocketNearAndFar : public COREAuton {
public:
	HatchLowRocketNearAndFar();
	void AddNodes();

private:
    Node * m_driveLowRocketNearSide = nullptr;
    Node * m_placeHatchOnLowNearSideRocket = nullptr;
    Node * m_driveToPlayerStation = nullptr;
    Node * m_grabHatchFromPlayerStation = nullptr;
    Node * m_driveToFarSideRocket = nullptr;
    Node * m_placeHatchOnFarSideRocket = nullptr;

};