#include <LiftSubsystem.h>
#include <frc/WPILib.h>
#include <Robot.h>
#include <CORERobotLib.h>

using namespace CORE;

LiftSubsystem::LiftSubsystem() : m_firstLevelHatch("First Level Hatch Height", 0.0),
                                 m_firstLevelCargo("First Level Cargo Height", 0.0),
                                 m_secondLevelHatch("Second Level Hatch Height", 0.0),
                                 m_secondLevelCargo("Second Level Cargo Height", 0.0),
                                 m_thirdLevelHatch("Third Level Hatch Height", 0.0),
                                 m_thirdLevelCargo("Third Level Cargo Height", 0.0),
                                 m_rightLiftMotor(16),
                                 m_leftLiftMotor(17) {

}

void LiftSubsystem::robotInit(){

}

void LiftSubsystem::teleopInit(){
    
}

void LiftSubsystem::teleop(){
    
}

void LiftSubsystem::SetLift(double speed){

}

void LiftSubsystem::SetRequestedPosition(double position){

}


void LiftSubsystem::SetRequestedSpeed(double speed){

}

double LiftSubsystem::GetLiftPosition(){

}

double LiftSubsystem::GetLiftInches(){
    // return m_liftInches;
}

void LiftSubsystem::ResetEncoder(){

}

void LiftSubsystem::SetFirstLevelHatchHeight() {
    SetRequestedPosition(m_firstLevelHatch.Get());
}

void LiftSubsystem::SetSecondLevelHatchHeight() {
    SetRequestedPosition(m_secondLevelHatch.Get());
}

void LiftSubsystem::SetThirdLevelHatchHeight() {
    SetRequestedPosition(m_thirdLevelHatch.Get());
}

void LiftSubsystem::SetFirstLevelCargoHeight() {
    SetRequestedPosition(m_firstLevelHatch.Get());
}

void LiftSubsystem::SetSecondLevelCargoHeight() {
    SetRequestedPosition(m_secondLevelHatch.Get());
}

void LiftSubsystem::SetThirdLevelCargoHeight() {
    SetRequestedPosition(m_thirdLevelHatch.Get());
}