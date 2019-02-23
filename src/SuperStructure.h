#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <CargoSubsystem.h>
#include <DriveSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>
#include <LiftSubsystem.h>
#include <Robot.h>

using namespace CORE;

enum class LiftState{
	LiftHatchFirstLevel,
	LiftCargoFirstLevel,
	LiftHatchSecondLevel,
	LiftCargoSecondLevel,
	LiftHatchThirdLevel,
	LiftCargoThirdLevel,
	LiftCargoIntake,
	LiftUnknownLevel
}

enum class CargoState{
	CargoIntake,
	CargoOutake,
	CargoLift,
	CargoNeutral
}

enum class HatchIntakeState{
	HatchIntakeIntake,
	HatchIntakeOutake,
	HatchIntakeNeutral
}

enum class HatchScorerState{
	HatchScorerIntake,
	HatchScorerOutake,
	HatchScorerNeutral
}


class SuperStructure : public CORESubsystem, public CORETask {
  public:
	SuperStructure();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void PostLoopTask() override;
	SuperStructure setLiftWantedState();
	SuperStructure setCargoWantedState();
	SuperStructure setHatchIntakeWantedState();
	SuperStructure setHatchScorerWantedState();

private:
	CargoSubsystem * m_cargoSubsystem;
	HatchIntakeSubsystem * m_hatchIntakeSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;
	LiftSubsystem * m_liftSubsystem;
	//DriveSubsystem * m_driveSubsystem;

	LiftState m_liftState;
	CargoState m_cargoState;
	HatchIntakeState m_hatchIntakeState;
	HatchScorerState m_hatchScorerState;

	LiftState m_wantedLiftState;
	CargoState m_wantedCargoState;
	HatchIntakeState m_wantedHatchIntakeState;
	HatchScorerState m_wantedHatchScorerState;

	// Lift States
	LiftState liftHatchFirstLevel();
	LiftState liftCargoFirstLevel();
	LiftState liftHatchSecondLevel();
	LiftState liftCargoSecondLevel();
	LiftState liftHatchThirdLevel();
	LiftState liftCargoThirdLevel();
	//LiftState LiftCargoIn();
	
	// Cargo States
	CargoState cargoIntake();
	CargoState cargoOutake();
	//CargoState CargoNeutral();

	// Hatch Intake States
	HatchIntakeState hatchIntakeIntake();
	HatchIntakeState hatchIntakeOutake();
	//HatchIntakeState HatchIntakeNeutral();

	// Hatch Scorer States
	HatchScorerState hatchScorerIntake();
	HatchScorerState hatchScorerOutake();
	//HatchScorerState HatchScorerNeutral();

	void StartTimer();
	double GetTime();
	CORETimer m_delayTimer;
};
