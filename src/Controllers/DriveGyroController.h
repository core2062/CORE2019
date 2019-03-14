#pragma once

#include "COREFramework/COREScheduler.h"
#include "WaypointFollower/Tank/TankRotation2d.h"

using namespace CORE;

class DriveGyroController : public COREController {
public:
	DriveGyroController(double target = 0.0, double tolerance = 1.0, bool relative = false);
	void Init(double target, double tolerance = 1.0, bool relative = false);
	void PostLoopTask() override;
	void EnabledLoop() override;
	bool IsDone();
private:
	double GetError();
	TankRotation2d m_target;
	double m_tolerance = 0.0;
	double m_error = 0.0;
};
