#pragma once

#include "COREFramework/COREScheduler.h"
#include "WaypointFollower/Tank/TankWaypointFollower.h"
#include "WaypointFollower/Tank/TankRobotFrame.h"

class DriveWaypointController : public COREController {
private:
	TankPath m_path;
	TankTracker * m_tracker;
	TankAdaptivePursuit m_pursuit;
	

public:
	DriveWaypointController();
	void PreLoopTask() override;
	void PostLoopTask() override;
	void EnabledLoop() override;
	void Enable() override;
	void Disable() override;
	void AutonInitTask() override;

	void StartPath(TankPath path, bool reversed = false, double maxAccel = 25.0, double tolerance = .25, bool gradualStop = true, double lookahead = 24.0);
	void ResetTracker(TankPosition2d initialPos);
	bool IsDone();
	bool CheckEvent(std::string event);
	void UpdatePathFollower();

	TankRobotFrame * frame = nullptr;

};
