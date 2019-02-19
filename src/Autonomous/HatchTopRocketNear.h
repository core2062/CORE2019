#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchTopRocketNear : public COREAuton {
public:
	HatchTopRocketNear();
	void AddNodes();

private:
	Node * m_driveForwardToRocket = nullptr;
    Node * m_placeHatchOnTopRocket = nullptr;
    Node * m_lowerLiftToFirstLevel = nullptr;
};