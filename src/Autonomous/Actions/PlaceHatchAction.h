#pragma once

#include <CORERobotLib.h>

enum PlaceHatch{
    CLOSE,
    EXTEND,
    RETRACT
};

class PlaceHatchAction : public COREAutonAction {
public:
    PlaceHatchAction();
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    PlaceHatch m_PlaceHatchRequestedAction;
};