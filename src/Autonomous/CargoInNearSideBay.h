#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class CargoInNearSideBay : public COREAuton {
public:
    CargoInNearSideBay();
	void AddNodes();

private:
	Node * m_driveForwardToNearSideCargoBay = nullptr;
    Node * m_placeCargoInNearSideBay = nullptr;
};