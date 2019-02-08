#pragma once

#include <CORERobotLib.h>


class PlaceHatchAction : public COREAutonAction {
public:
    PlaceHatchAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};