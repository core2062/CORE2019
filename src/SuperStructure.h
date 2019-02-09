#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include <CargoSubsystem.h>
#include <DriveSubsystem.h>
#include <HatchIntakeSubsystem.h>
#include <HatchScorerSubsystem.h>
#include <LiftSubsystem.h>

using namespace CORE;


#include "Robot.h"

enum class WantedState {
	WantToPickupGroundHatch,
	WantToPickupGroundCargo,
	WantToPickupFeederHatch,
	WantToPickupFeederCargo,
	WantToScoreHatchBottomRocket,
	WantToScoreHatchMiddleRocket,
	WantToScoreHatchTopRocket,
	WantToScoreHatchCargoShip,
	WantToScoreCargoBottomRocket,
	WantToScoreCargoMiddleRocket,
	WantToScoreCargoTopRocket,
	WantToScoreCargoCargoShip,
	WantToDoNothing,
	MANUAL
};


enum class SystemState {
	Transit,
	GrabbingCargo,
	GrabbingHatch,
	TopRocketCargoScoring,
	MiddleRocketCargoScoring,
	BottomRocketCargoScoring,
	TopRocketHatchScoring,
	MiddleRocketHatchScoring,
	BottomRocketHatchScoring,
	CargoShipHatchScoring,
	CargoShipCargoScoring,
	FeederCargo,
	FeederHatch

};

class SuperStructure : public CORESubsystem, public CORETask {
  public:
	SuperStructure();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void PostLoopTask() override;

private:
	CargoSubsystem * m_cargoSubsystem;
	HatchIntakeSubsystem * m_hatchIntakeSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;
	LiftSubsystem * m_liftSubsystem;


	SystemState	m_systemState;

	SystemState handleTransit();
	SystemState handleTopRocketCargoScoring();
	SystemState handleMiddleRocketCargoScoring();
	SystemState handleBottemRocketCargoScoring();
	SystemState handleTopRocketHatchScoring();
	SystemState handleMiddleRocketHatchScoring();
	SystemState	handleBottemRocketHatchScoring();
	SystemState handleCargoShipCargoScoring();
	SystemState handleFeederCargo();
	SystemState handleFeederHatch();


//e.
};