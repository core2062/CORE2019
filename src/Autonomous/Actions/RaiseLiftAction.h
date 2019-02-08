#pragma once

#include <CORERobotLib.h>


class RaiseLiftAction : public COREAutonAction {
public:
    RaiseLiftAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};