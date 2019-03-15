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
	Node * m_driveForwardToPlayerStation = nullptr;
	Node * m_grabHatchFromPlayerStation = nullptr;
	Node * m_driveForwardToOtherFrontCargoBay = nullptr;
	Node * m_placeHatchOnOtherFrontCargoBay = nullptr;
};