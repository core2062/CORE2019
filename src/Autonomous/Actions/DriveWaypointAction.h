#pragma once

#include <CORERobotLib.h>
#include <DriveSubsystem.h>

class DriveWaypointAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

