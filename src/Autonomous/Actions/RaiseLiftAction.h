#pragma once

#include <CORERobotLib.h>
#include <COREUtilities/COREConstant.h>

enum RaiseLift{
    FirstLevelCargo,
    SecondLevelCargo,
    ThirdLevelCargo,
    FirstLevelHatch,
    SecondLevelHatch,
    ThirdLevelHatch
};

class RaiseLiftAction : public COREAutonAction {
public:
    RaiseLiftAction(RaiseLift Action);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
COREConstant<double> m_FirstLevelCargo;
COREConstant<double> m_SecondLevelCargo;
COREConstant<double> m_ThirdLevelCargo;
COREConstant<double> m_FirstLevelHatch;
COREConstant<double> m_SecondLevelHatch;
COREConstant<double> m_ThirdLevelHatch;
RaiseLift m_RaiseLiftRequestedAction;
};