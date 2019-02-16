#pragma once

#include <CORERobotLib.h>


class DriveWaypointAction : public COREAutonAction {
public:
    DriveWaypointAction();
    void ActionInit();
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd();
private:
     Path m_path;
    bool m_reversed;
    double m_tolerance;
    double m_maxAccel;
    double m_maxAngAccel;
    bool m_gradualStop;
    double m_lookahead;
    bool m_resetPosition;
    Position2d m_startPos; 
};
