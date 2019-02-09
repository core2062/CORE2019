#pragma once

#include <CORERobotLib.h>

enum RaiseLift{
    FirstLevelCargo,
    SecondLevelCargo,
    ThridLevelCargo,
    FirstLevelHatch,
    SecondLevelHatch,
    ThridLevelHatch
};

class RaiseLiftAction : public COREAutonAction {
public:
    RaiseLiftAction();
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
};