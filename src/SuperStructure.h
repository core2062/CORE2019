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
	FeederHatch

};

class SuperStructure : public CORESubsystem, public CORE::CORETask {
  public:
	SuperStructure();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void PostLoopTask() override;
	SuperStructure setWantedState();

private:
	CargoSubsystem * m_cargoSubsystem;
	HatchIntakeSubsystem * m_hatchIntakeSubsystem;
	HatchScorerSubsystem * m_hatchScorerSubsystem;
	LiftSubsystem * m_liftSubsystem;
	DriveSubsystem * m_driveSubsystem;

	SystemState	m_systemState;

	SystemState handleTransit();
	SystemState HandleTopRocketCargoScoring();
	SystemState HandleMiddleRocketCargoScoring();
	SystemState HandleBottomRocketCargoScoring();
	SystemState HandleTopRocketHatchScoring();
	SystemState HandleMiddleRocketHatchScoring();
	SystemState	HandleBottomRocketHatchScoring();
	SystemState HandleCargoShipCargoScoring();
	SystemState HandleCargoShipHatchScoring();
	SystemState HandleFeederHatch();
};
