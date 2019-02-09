#pragma once
#include <CORERobotLib.h>


class DriveDistanceAction : public COREAutonAction {
public:
    DriveDistanceAction();
    void ActionInit() override;
CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    CORETimer Timer;
};

