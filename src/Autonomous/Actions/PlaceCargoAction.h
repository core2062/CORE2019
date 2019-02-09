#pragma once

#include <CORERobotLib.h>

enum PlaceCargo{
    OUTTAKE
};

class PlaceCargoAction : public COREAutonAction {
public:
    PlaceCargoAction();
    void ActionInit(PlaceCargo i);
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    PlaceCargo m_PlaceCargoRequestedAction;
};