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

class Autonomous: public COREAuton {
    public:
    Autonomous();
    void AddNodes() override;
    // void AutonInit() override;
    // void Auton() override;
    // bool Complete() override;
    private:
    /*DriveSubsystem * m_driveSubsystem;
	CargoSubsystem * m_cargoSubsystem;
	//HatchIntakeSubsystem hatchSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;
	LiftSubsystem * m_liftSubsystem;*/
    Node * autonLoop;

};