#pragma once

#include <CORERobotLib.h>

enum PlaceCargo{
    OUTTAKE_CARGO
};

class PlaceCargoAction : public COREAutonAction {
public:
    PlaceCargoAction(PlaceCargo Action);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    PlaceCargo m_placeCargoRequestedAction;
};