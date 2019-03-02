#pragma once

#include <CORERobotLib.h>

class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction(TankPath path);
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
    TankPath m_path;
    bool m_reversed;
    double m_tolerance;
    double m_maxAccel;
    bool m_gradualStop;
    double m_lookahead;
    TankPosition2d m_startPos; 
};
