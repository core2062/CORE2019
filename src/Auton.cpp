#include "Auton.h"
#include <Robot.h>
#include <frc/WPILib.h>

Autonomous::Autonomous() : COREAuton("Sam Drive") {
}

void Autonomous::AddNodes() {
    autonLoop = new Node(15, new SandstormAction());
    AddFirstNode(autonLoop);
}
