#include <HatchScorerSubsystem.h>
#include <frc/WPILib.h>
#include "Robot.h"

//TODO:Fill these in with actual port numbers
HatchScorerSubsystem::HatchScorerSubsystem() : m_solenoidExtend(0, 0, 0),
                                               m_solenoidGrab(0, 0, 0),
                                               m_solenoidRelease(0, 0, 0) {

}

void HatchScorerSubsystem::robotInit(){

}

void HatchScorerSubsystem::teleopInit(){
    
}

void HatchScorerSubsystem::teleop(){
    
}

void HatchScorerSubsystem::ActuateClaw(){

/*use a bool to tell if the claw is opened or not. if it is when the button is pressed it will close.
if it is closed it will open*/

}

void HatchScorerSubsystem::SetClawState(){

}

