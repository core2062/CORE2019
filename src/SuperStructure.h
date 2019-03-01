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

enum class LiftState {
	LiftHatchFirstLevel,
	LiftCargoFirstLevel,
	LiftHatchSecondLevel,
	LiftCargoSecondLevel,
	LiftHatchThirdLevel,
	LiftCargoThirdLevel,
	LiftCargoAfterIntake,
	// what about scoring the hatch and cargo on the cargo ship?
	LiftUnknownLevel
};

enum class CargoState {
	CargoIntake,
	CargoOuttake,
	CargoLift, // this might be better left to the lift subsystem
	CargoNeutral
};

enum class HatchIntakeState {
	HatchIntakeIntake,
	HatchIntakeOuttake,
	HatchIntakeNeutral
};

enum class HatchScorerState {
	HatchScorerIntake,
	HatchScorerOuttake,
	HatchScorerNeutral
};

class SuperStructure : public CORESubsystem, public CORETask {
public:
	SuperStructure();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void PostLoopTask() override;

private:
	LiftSubsystem * m_liftSubsystem;
	CargoSubsystem * m_cargoSubsystem;
	HatchIntakeSubsystem * m_hatchIntakeSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;

	LiftState m_liftState;
	CargoState m_cargoState;
	HatchIntakeState m_hatchIntakeState;
	HatchScorerState m_hatchScorerState;

	LiftState m_wantedLiftState;
	CargoState m_wantedCargoState;
	HatchIntakeState m_wantedHatchIntakeState;
	HatchScorerState m_wantedHatchScorerState;

	// Lift States
	LiftState LiftHatchFirstLevel();
	LiftState LiftCargoFirstLevel();
	LiftState LiftHatchSecondLevel();
	LiftState LiftCargoSecondLevel();
	LiftState LiftHatchThirdLevel();
	LiftState LiftCargoThirdLevel();
	LiftState CargoLiftLevel();
	LiftState CargoIntakeLiftLevel();

	// Cargo States
	CargoState CargoIntake();
	CargoState CargoOuttake();
	//CargoState CargoNeutral();

	// Hatch Intake States
	HatchIntakeState HatchIntakeIntake();
	HatchIntakeState HatchIntakeOuttake();
	//HatchIntakeState HatchIntakeNeutral();

	// Hatch Scorer States
	HatchScorerState HatchScorerIntake();
	HatchScorerState HatchScorerOuttake();
	//HatchScorerState HatchScorerNeutral();
};
