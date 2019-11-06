#pragma once

#include <memory>
#include <CORERobotLib.h>

using namespace CORE;

class WaypointTestAuton : public COREAuton {
public:
    WaypointTestAuton();
	void AddNodes();

private:
	Node * m_driveForward;
};