#pragma once

#include <memory>
#include <CORERobotLib.h>

using namespace CORE;

class GrabHatchActionTestAuton : public COREAuton {
public:
    GrabHatchActionTestAuton();
	void AddNodes();

private:
	Node * m_grabCargo = nullptr;
};