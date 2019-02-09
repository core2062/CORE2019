#include <Autonomous/Actions/RaiseLiftAction.h>
#include <Robot.h>
#include <CORERobotLib.h>
#include <COREUtilities/COREConstant.h>

RaiseLiftAction::RaiseLiftAction(RaiseLift i):
    m_FirstLevelCargo("Bottom cargo height value"),
    m_SecondLevelCargo("Middle cargo height value"),
    m_ThirdLevelCargo("Top cargo height value"),
    m_FirstLevelHatch("Bottom hatch height value"),
    m_SecondLevelHatch("Middle hatch height value"),
    m_ThirdLevelHatch("Top hatch height value")
    {
    m_RaiseLiftRequestedAction = i;
}

void RaiseLiftAction::ActionInit() {
    
}

CORE::COREAutonAction::actionStatus RaiseLiftAction::Action() {
    
    switch(m_RaiseLiftRequestedAction) {
        case FirstLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_FirstLevelCargo.Get());
		break;
        case SecondLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_SecondLevelCargo.Get());
		break;
        case ThirdLevelCargo:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_ThirdLevelCargo.Get());
		break;
        case FirstLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_FirstLevelHatch.Get());
		break;
        case SecondLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_SecondLevelHatch.Get());
		break;
        case ThirdLevelHatch:
		Robot::GetInstance()->liftSubsystem.SetRequestedPosition(m_ThirdLevelHatch.Get());
		break;
    }
    return COREAutonAction::actionStatus::END;


}

void RaiseLiftAction::ActionEnd() {

}
