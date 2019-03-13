#pragma once

#include <CORERobotLib.h>
#include <iostream>

using namespace CORE;

class SandstormAction : public COREAutonAction {
public:
    SandstormAction();
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;

};