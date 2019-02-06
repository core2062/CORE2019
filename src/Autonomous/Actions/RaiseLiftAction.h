#pragma once

#include <CORERobotLib.h>
#include <LiftSubsystem.h>

class RaiseLiftAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};