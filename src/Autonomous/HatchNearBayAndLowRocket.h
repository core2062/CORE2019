#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchNearBayAndLowRocket : public COREAuton {
public:
	HatchNearBayAndLowRocket();
	void AddNodes();

private:
	Node * m_driveForwardFirstBaySideCargoShip = nullptr;
	Node * m_placeHatchOnNearSideBay = nullptr;
	Node * m_driveToPlayerStation = nullptr;
	Node * m_grabHatchFromPlayerStation = nullptr;
	Node * m_driveToLowNearRocket = nullptr;
	Node * m_placeHatchOnLowRocket = nullptr;
};