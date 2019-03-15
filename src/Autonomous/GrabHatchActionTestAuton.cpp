#include "GrabHatchActionTestAuton.h"
#include "Actions/GrabHatchAction.h"

GrabHatchActionTestAuton::GrabHatchActionTestAuton() :
	COREAuton("Grab Hatch Action Test Auton") {
}

void GrabHatchActionTestAuton::AddNodes() {
    m_grabCargo = new Node(5, new GrabCargoAction(GrabCargo::INTAKE));
    AddFirstNode(m_grabCargo);
}