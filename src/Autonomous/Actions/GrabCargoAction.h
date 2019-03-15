#pragma once

#include <CORERobotLib.h>

enum GrabCargo{
    INTAKE,
    NEUTRAL
};

class GrabCargoAction : public COREAutonAction {
public:
    GrabCargoAction(GrabCargo Action);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    GrabCargo m_grabCargoRequestedAction;
};
