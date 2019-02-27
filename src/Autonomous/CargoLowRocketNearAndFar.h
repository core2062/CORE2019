#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoLowRocketNearAndFar : public COREAuton {
public:
	CargoLowRocketNearAndFar();
	void AddNodes();

private:
    Node * m_driveLowRocketNearSide = nullptr;
    Node * m_placeCargoOnLowNearSideRocket = nullptr;
    Node * m_driveToPlayerStation = nullptr;
    Node * m_grabCargoFromPlayerStation = nullptr;
    Node * m_driveToFarSideRocket = nullptr;
    Node * m_placeCargoOnFarSideRocket = nullptr;

};