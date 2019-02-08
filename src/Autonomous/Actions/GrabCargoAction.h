#pragma once

#include <CORERobotLib.h>

class GrabCargoAction : public COREAutonAction {
public:
    GrabCargoAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

