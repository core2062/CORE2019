#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <CargoSubsystem.h>
#include <DriveSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>
#include <LiftSubsystem.h>

using namespace CORE;

enum class LiftState {
	LiftHatchFirstLevel,
	LiftCargoFirstLevel,
	LiftHatchSecondLevel,
	LiftCargoSecondLevel,
	LiftHatchThirdLevel,
	LiftCargoThirdLevel,
	LiftCargoShipHatchLevel,
	LiftCargoShipCargoLevel,
	LiftLevelAfterCargoIntake,
	LiftLevelToCargoIntake,
	LiftUnknownLevel
};
	//// what about scoring the hatch and cargo on the cargo ship?

enum class CargoState {
	CargoIntake,
	CargoOuttake,
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
	LiftState liftHatchFirstLevel();
	LiftState liftCargoFirstLevel();
	LiftState liftHatchSecondLevel();
	LiftState liftCargoSecondLevel();
	LiftState liftHatchThirdLevel();
	LiftState liftCargoThirdLevel();
	LiftState liftCargoShipCargoLevel();
	LiftState liftCargoShipHatchLevel();
	LiftState liftLevelAfterCargoIntake();
	LiftState liftLevelToIntakeCargo();

	// Cargo States
	CargoState cargoIntake();
	CargoState cargoOuttake();
	//CargoState CargoNeutral();

	// Hatch Intake States
	HatchIntakeState hatchIntakeIntake();
	HatchIntakeState hatchIntakeOuttake();
	//HatchIntakeState HatchIntakeNeutral();

	// Hatch Scorer States
	HatchScorerState HatchScorerIntake();
	HatchScorerState HatchScorerOuttake();
	//HatchScorerState HatchScorerNeutral();
};
