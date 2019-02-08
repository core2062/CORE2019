#pragma once

#include <CORERobotLib.h>



class PlaceCargoAction : public COREAutonAction {
public:
    PlaceCargoAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};