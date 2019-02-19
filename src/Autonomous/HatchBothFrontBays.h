#pragma once

#include <memory>
#include <CORERobotLib.h>
#include "Actions.h"

using namespace CORE;

class HatchBothFrontBays : public COREAuton {
public:
	HatchBothFrontBays();
	void AddNodes();

private:
	Node * m_driveForwardToFrontCargoBay = nullptr;
    Node * m_placeHatchOnFrontCargoBay = nullptr;
};