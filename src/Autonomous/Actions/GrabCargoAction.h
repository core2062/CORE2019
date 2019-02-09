#pragma once

#include <CORERobotLib.h>

enum GrabCargo{
    INTAKE
};

class GrabCargoAction : public COREAutonAction {
public:
    GrabCargoAction();
    void ActionInit(GrabCargo i);
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
GrabCargo m_GrabCargoRequestedAction;

};

