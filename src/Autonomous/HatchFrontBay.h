#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchFrontBay : public COREAuton {
public:
	HatchFrontBay();
	void AddNodes() override;

private:
	Node * m_driveForwardToFrontCargoBay = nullptr;
    Node * m_placeHatchOnFrontCargoBay = nullptr;
};