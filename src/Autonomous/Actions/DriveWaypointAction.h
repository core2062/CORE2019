#pragma once

#include <CORERobotLib.h>


class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction();
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
};

