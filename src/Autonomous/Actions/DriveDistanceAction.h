#pragma once
#include <CORERobotLib.h>


class DriveDistanceAction : public COREAutonAction {
public:
    DriveDistanceAction();
    void ActionInt();
CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
};

