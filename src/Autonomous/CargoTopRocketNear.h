#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoTopRocketNear : public COREAuton {
public:
	CargoTopRocketNear();
	void AddNodes();

private:
	Node * m_drvieForwardToRocket = nullptr;
    Node * m_placeCargoOnTopRocket = nullptr;
    Node * m_lowerLiftToFirstLevel = nullptr;
};