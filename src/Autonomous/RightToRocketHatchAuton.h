#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>

using namespace CORE;
using namespace std;

class RightToRocketHatchAuton: public COREAuton {
    public:
    RightToRocketHatchAuton();
    void AddNodes() override;
    Node * m_driveToRocket;
    Node * m_placeHatch;

};