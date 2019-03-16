#pragma once

#include <CORERobotLib.h>
#include <iostream>

using namespace CORE;

class TeleopAction : public COREAutonAction {
public:
    TeleopAction();
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;

};