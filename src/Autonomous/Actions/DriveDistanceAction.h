#pragma once

#include <CORERobotLib.h>
#include <DriveSubsystem.h>


class DriveDistanceAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};

