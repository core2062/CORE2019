#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchNearBay : public COREAuton {
public:
	HatchNearBay();
	void AddNodes();

private:
	Node * m_driveForwardToNearSideCargoBay = nullptr;
    Node * m_placeHatchOnNearSideBay = nullptr;
};