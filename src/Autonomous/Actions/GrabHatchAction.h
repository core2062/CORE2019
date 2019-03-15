#pragma once

#include <CORERobotLib.h>

enum GrabHatch{
    OPEN,
    PUSH,
    PULL
};

class GrabHatchAction : public COREAutonAction {
public:
    GrabHatchAction(GrabHatch Action);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    GrabHatch m_grabHatchRequestedAction;
};

