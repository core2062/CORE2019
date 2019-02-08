#pragma once

#include <CORERobotLib.h>

class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction();
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

