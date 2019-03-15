#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchLowRocketNear : public COREAuton {
public:
	HatchLowRocketNear();
	void AddNodes();

private:
    Node * m_driveLowRocketNearSide = nullptr;
    Node * m_placeHatchOnLowNearSide = nullptr;
   
};