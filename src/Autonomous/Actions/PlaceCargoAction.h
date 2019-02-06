#pragma once

#include <CORERobotLib.h>
#include <CargoSubsystem.h>

class PlaceCargoAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};