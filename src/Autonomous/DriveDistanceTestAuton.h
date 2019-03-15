#pragma once

#include <memory>
#include <CORERobotLib.h>

using namespace CORE;

class DriveDistanceTestAuton : public COREAuton {
public:
    DriveDistanceTestAuton();
	void AddNodes();

private:
	Node * m_driveForward = nullptr;
};