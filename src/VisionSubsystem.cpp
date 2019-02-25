#include "VisionSubsystem.h"
#include "Math.h"
using namespace CORE;

VisionSubsystem::VisionSubsystem() : rocketPlaceDist("Rocket Place Distance", 22.5),
	                                 ultrakP("Ultrasonic kP", .03),
	                                 m_imageWidth("Image width", 640),
	                                 m_horizontalFieldOfView("Horizontal field of view", 61.9),
	                                 m_rocketApproachDist("Rocket Approach Distance", 24),
	                                 m_ultraToCenterDist("Ultrasonic To Robot Center Dist", 12.25),
	                                 m_rocketApproachSamples("Rocket Approach Samples", 30),
	                                 m_leftUltra(4),
	                                 m_rightUltra(5),
	                                 m_jumper(6) {

}

void VisionSubsystem::robotInit(){
	operatorJoystick->RegisterButton(COREJoystick::BACK_BUTTON);
	visionTable = NetworkTableInstance::GetTable("Vision");
	visionTable->PutNumber("piTime", -1);
	visionTable->PutNumber("targetX", -1);
	visionTable->PutBoolean("disableRocketVision", true);
	visionTable->PutBoolean("disableRocketVision", false);
	visionTable->PutBoolean("disableVision", false);

}

void VisionSubsystem::teleopInit(){
	visionTable->PutBoolean("disableRocketVision", true);
	visionTable->PutBoolean("disableVision", true);
}
void VisionSubsystem::teleop() {
	if (operatorJoystick->GetRisingEdge(COREJoystick::BACK_BUTTON)){
		//if the right button is pressed, switch the front camera to the back camera
		if (whichCamera == frontCamera){
			whichCamera = backCamera;
		} else {
			whichCamera = frontCamera;
		}
	}
	visionTable->PutString("camera", whichCamera);
}

void VisionSubsystem::PreLoopTask() {
	SmartDashboard::PutNumber("Ultra Distance", GetUltraDist());
	std::cout << "L: " << m_leftUltra.GetVoltage() << " R: " << m_rightUltra.GetVoltage() << " J: " << m_jumper.GetVoltage() << std::endl;
	double piTime = visionTable->GetNumber("piTime", -1);
	if(m_timeOffsets.size() < 30){
		if(piTime != -1){
			double botTime = Timer::GetFPGATimestamp();
			m_timeOffsets.push_back(botTime - piTime);
			m_timeOffset = 0;
			for(auto i : m_timeOffsets){
				m_timeOffset+=i;
			}
			m_timeOffset /= m_timeOffsets.size();
		}
	}

	double x = visionTable->GetNumber("targetX", -1);
	if(x == -1){
		m_rocketX = m_imageWidth.Get() * .5;
		return;
	}

	m_rocketX = x;
}

TankPath * VisionSubsystem::GetPath() {
	return &m_pathToRocket;
}

TankRobotFrame * VisionSubsystem::GetFrame(){
	return &m_visionFrame;
}

void VisionSubsystem::CalculatePath() {
	double x = visionTable->GetNumber("targetX", -1);

	if(x == -1){
		x = m_imageWidth.Get() * .5;
		CORELog::LogWarning("Couldn't See Vision Target!");
	}

	x = m_imageWidth.Get() - x;

	TankPosition2d capturePos = TankTracker::GetInstance()->GetLatestFieldToVehicle();
	double captureRot = capturePos.GetRotation().GetDegrees();
	std::cout << "X:" << capturePos.GetTranslation().GetX() << " Y:" <<
			capturePos.GetTranslation().GetY() << " T:" << capturePos.GetRotation().GetDegrees() << std::endl;

	TankRotation2d centerToY;

	if(captureRot > -29 && captureRot < 29){
		centerToY = capturePos.GetRotation();
		m_visionFrame = TankRobotFrame(TankPosition2d(capturePos.GetTranslation(), TankRotation2d::FromDegrees(0)));
	} else if (captureRot > 31 && captureRot < 89){
		centerToY = capturePos.GetRotation().RotateBy(TankRotation2d::FromDegrees(-60));
		m_visionFrame = TankRobotFrame(TankPosition2d(capturePos.GetTranslation(), TankRotation2d::FromDegrees(-60)));
	} else if (captureRot > -89 && captureRot < -31){
		centerToY = capturePos.GetRotation().RotateBy(TankRotation2d::FromDegrees(60));
		m_visionFrame = TankRobotFrame(TankPosition2d(capturePos.GetTranslation(), TankRotation2d::FromDegrees(60)));
	}

	std::cout << "deltaRot: " << centerToY.GetDegrees() << std::endl;

	double focalLen = m_imageWidth.Get() / (2 * tan(CORE::ToRadians(m_horizontalFieldOfView.Get() * .5)));

	double hAngle = atan((x-(m_imageWidth.Get() * .5 - .5)) / focalLen);
	double distToRocket = GetUltraDist();
	double forward = cos(hAngle) * distToRocket;
	double side = sin(hAngle) * distToRocket;

	TankTranslation2d rocketPos(-forward,-side);
	stringstream a;
	a << "FWD: " << rocketPos.GetX() << " SIDE: " << rocketPos.GetY() << std::endl;
	rocketPos = rocketPos.RotateBy(centerToY);
	a << "FWD: " << rocketPos.GetX() << " SIDE: " << rocketPos.GetY() << std::endl;
	CORELog::LogInfo(a.str());

	//MATH
	std::cout << "About To generate points, x at" << rocketPos.GetX() << std::endl;
	std::vector<TankWaypoint> points;
	points.push_back(TankWaypoint(TankTranslation2d(),100));
	int samples = m_rocketApproachSamples.Get();
	std::cout << "Taking " << samples << " Samples" << std::endl;
	double sampleDelta = fabs(rocketPlaceDist.Get() - m_rocketApproachDist.Get()) / (double)samples;
	for(int i = samples; i >= 0; i--){
		points.push_back(TankWaypoint(TankTranslation2d(rocketPos.GetX() + rocketPlaceDist.Get() + sampleDelta * i,
				rocketPos.GetY()), 100));
	}
	m_pathToRocket = TankPath(points);

	for(auto i : points){
		std::cout << "X:" << i.position.GetX() << " Y:" << i.position.GetY() << " Speed:" << i.speed << std::endl;
	}

	std::cout << "Done Calcing Vision" << std::endl;
}

TankRotation2d VisionSubsystem::GetError(){
	TankRotation2d current = TankTracker::GetInstance()->GetLatestFieldToVehicle().GetRotation();
	TankRotation2d target = m_targetRotation;
	return target.RotateBy(current.Inverse());
}

double VisionSubsystem::GetErrorPercent() {
	return (m_rocketX - (m_imageWidth.Get() * .5)) / m_imageWidth.Get();
}

void VisionSubsystem::AutonInitTask() {
	visionTable->PutBoolean("disableRocketVision", false);
	visionTable->PutBoolean("disableVision", false);
}

double VisionSubsystem::GetUltraDist() {
	double scale = (1024.0 / 2.54); //403.1496
	double l = (1000.0 * (m_leftUltra.GetVoltage())) / ((m_jumper.GetVoltage() * 1000.0) / scale);
	double r = (1000.0 * (m_rightUltra.GetVoltage())) / ((m_jumper.GetVoltage() * 1000.0) / scale);
	double v;
	if(fabs(l-r) > 10.0){
		if(l>r){
			v = r;
		} else {
			v = l;
		}
	}else{
		v = (l + r) * .5;
	}
	return v;
}

double VisionSubsystem::GetRocketX() {
	return visionTable->GetNumber("rocketX", -1);
}