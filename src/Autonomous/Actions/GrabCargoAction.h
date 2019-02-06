#pragma once

#include <CORERobotLib.h>
#include <CargoSubsystem.h>

class GrabCargoAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

