#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchNearBayAndLowRocket : public COREAuton {
public:
	HatchNearBayAndLowRocket();
	void addNodes();

private:
	Node * m_driveForwardFirstBaySideCargoShip = nullptr;
};