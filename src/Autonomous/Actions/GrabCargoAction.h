#pragma once

#include <CORERobotLib.h>

enum GrabCargo{
    INTAKE
};

class GrabCargoAction : public COREAutonAction {
public:
    GrabCargoAction();
    void ActionInit(GrabCargo Action);
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
GrabCargo m_grabCargoRequestedAction;

};

