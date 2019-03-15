#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoMidRocketNear : public COREAuton {
public:
	CargoMidRocketNear();
	void AddNodes();

private:
	Node * m_driveForwardToRocket = nullptr;
    Node * m_placeCargoOnMidRocket = nullptr;
    Node * m_lowerLiftToFirstLevel = nullptr;
};