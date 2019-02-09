#pragma once

#include <CORERobotLib.h>

enum GrabHatch{
    OPEN,
    EXTEND,
    RETRACT
};

class GrabHatchAction : public COREAutonAction {
public:
    GrabHatchAction(GrabHatch i);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    GrabHatch m_GrabHatchRequestedAction;
};
