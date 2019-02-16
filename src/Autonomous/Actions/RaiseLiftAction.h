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
COREConstant<double> m_firstLevelCargo;
COREConstant<double> m_secondLevelCargo;
COREConstant<double> m_thirdLevelCargo;
COREConstant<double> m_firstLevelHatch;
COREConstant<double> m_secondLevelHatch;
COREConstant<double> m_thirdLevelHatch;
RaiseLift m_raiseLiftRequestedAction;
};