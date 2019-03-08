#include "Auton.h"
#include <Robot.h>
#include <frc/WPILib.h>

Autonomous::Autonomous() : COREAuton("Teleop in Autonomous") {
}

void Autonomous::AddNodes() {
    autonLoop = new Node(15, new SandstormAction());
    AddFirstNode(autonLoop);
}

// void Autonomous::AutonInit(){
// 	COREScheduler::teleopInit();
// }

// void Autonomous::Auton() {
// 	COREScheduler::teleop();
// }

// bool Autonomous::Complete() {
//     return false;
// }
