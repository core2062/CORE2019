#pragma once

#include <string>

#include <frc/WPILib.h>
#include <CORERobotLib.h>
#include <AutonNode.h>
/*#include <DriveSubsystem.h>
#include <CargoSubsystem.h>
#include <LiftSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>*/

using namespace CORE;
using namespace std;

class Autonomous: public COREAuton, public CORETask {
    public:
    Autonomous();
    void AddNodes() override;
    private:
    /*DriveSubsystem * m_driveSubsystem;
	CargoSubsystem * m_cargoSubsystem;
	//HatchIntakeSubsystem hatchSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;
	LiftSubsystem * m_liftSubsystem;*/
    Node * autonLoop;

};