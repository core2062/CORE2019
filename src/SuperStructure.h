#pragma once

#include "ctre/Phoenix.h"
#include <CORERobotLib.h>

using namespace CORE;


#include "Robot.h"

enum class WantedState
{
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
	MANUAL
};


enum class SystemState
{
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

class SuperStructure : public CORESubsystem
{
  public:
	SuperStructure();
	
};