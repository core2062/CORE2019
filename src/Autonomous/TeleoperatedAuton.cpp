#include <Autonomous/Actions.h>
#include <Robot.h>
#include <frc/WPILib.h>
#include "TeleoperatedAuton.h"

TeleoperatedAutonomous::TeleoperatedAutonomous() : COREAuton("Teleop in Autonomous") {
}

void TeleoperatedAutonomous::AddNodes() {
    autonLoop = new Node(15, new TeleopAction());
    AddFirstNode(autonLoop);
}