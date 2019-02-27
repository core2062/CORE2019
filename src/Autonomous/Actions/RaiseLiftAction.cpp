#include <Autonomous/Actions/RaiseLiftAction.h>
#include <Robot.h>

RaiseLiftAction::RaiseLiftAction(RaiseLift Action):
    m_firstLevelCargo("Bottom cargo height value"),
    m_secondLevelCargo("Middle cargo height value"),
    m_thirdLevelCargo("Top cargo height value"),
    m_firstLevelHatch("Bottom hatch height value"),
    m_secondLevelHatch("Middle hatch height value"),
    m_thirdLevelHatch("Top hatch height value") {
    m_raiseLiftRequestedAction = Action;
}

void RaiseLiftAction::ActionInit() {
    
}

CORE::COREAutonAction::actionStatus RaiseLiftAction::Action() {
    switch(m_raiseLiftRequestedAction) {
        case FirstLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_firstLevelCargo.Get());
		break;
        case SecondLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_secondLevelCargo.Get());
		break;
        case ThirdLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_thirdLevelCargo.Get());
		break;
        case FirstLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_firstLevelHatch.Get());
		break;
        case SecondLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_secondLevelHatch.Get());
		break;
        case ThirdLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_thirdLevelHatch.Get());
		break;
    }
    return COREAutonAction::actionStatus::END;


}

void RaiseLiftAction::ActionEnd() {

}
