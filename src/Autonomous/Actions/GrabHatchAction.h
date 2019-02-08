#pragma once

#include <CORERobotLib.h>


class GrabHatchAction : public COREAutonAction {
public:
    GrabHatchAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

