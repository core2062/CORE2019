#pragma once

#include <CORERobotLib.h>
#include <HatchScorerSubsystem.h>

class PlaceHatchAction : public COREAutonAction {
public:
    void ActionInt();
    actionStatus Action() override;
    void ActionEnd();
private:
};