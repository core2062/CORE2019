#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoLowRocketNear : public COREAuton {
public:
	CargoLowRocketNear();
	void AddNodes();

private:
    Node * m_driveLowRocketNearSide = nullptr;
    Node * m_placeCargoOnLowNearSide = nullptr;
   
};