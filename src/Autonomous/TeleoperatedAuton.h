#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>

using namespace CORE;
using namespace std;

class TeleoperatedAutonomous: public COREAuton {
public:
    TeleoperatedAutonomous();
    void AddNodes() override;
private:
    Node * m_autonLoop;

};