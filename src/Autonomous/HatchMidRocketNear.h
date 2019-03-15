#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchMidRocketNear : public COREAuton {
public:
	HatchMidRocketNear();
	void AddNodes();

private:
	Node * m_driveForwardToRocket = nullptr;
    Node * m_placeHatchOnMidRocket = nullptr;
    Node * m_lowerLiftToFirstLevel = nullptr;
};