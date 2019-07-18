#pragma once

#include <string>

#include <AutonNode.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>
/*#include <DriveSubsystem.h>
#include <CargoSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>*/
#include <LiftSubsystem.h>

using namespace CORE;
using namespace std;

class Autonomous : public COREAuton {
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
    Node* autonLoop;
};