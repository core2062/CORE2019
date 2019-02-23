#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoNearAndMidSideBay : public COREAuton {
public:
	CargoNearAndMidSideBay();
	void AddNodes();

private:
    Node * m_driveToNearSideBay = nullptr;
    Node * m_placeCargoInNearSideBay = nullptr;
    Node * m_driveToCargoDepot = nullptr;
    Node * m_grabCargoFromCargoDepot = nullptr;
    Node * m_driveToMidSideBay = nullptr;
    Node * m_placeCargoInMidSideBay = nullptr;

};