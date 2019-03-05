#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchNearAndMidBay : public COREAuton {
public:
	HatchNearAndMidBay();
	void AddNodes();

private:
	Node * m_driveForwardFirstBaySideCargoShip = nullptr;
	Node * m_placeHatchOnNearSideBay = nullptr;
	Node * m_driveToPlayerStation = nullptr;
	Node * m_grabHatchFromPlayerStation = nullptr;
	Node * m_driveToMidSideCargoBay = nullptr;
	Node * m_placeHatchOnMidSideCargoBay = nullptr;
};