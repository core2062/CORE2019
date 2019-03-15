#pragma once

#include <memory>
#include <CORERobotLib.h>

using namespace CORE;

class GrabCargoActionTestAuton : public COREAuton {
public:
    GrabCargoActionTestAuton();
	void AddNodes();

private:
	Node * m_grabCargo = nullptr;
};