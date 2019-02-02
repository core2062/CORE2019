
#include "VisionSubsystem.h"

VisionSubsystem::VisionSubsystem() : m_cargoRightUltra(ULTRASONIC_CARGO_RIGHT_CHANNEL),
                                     m_hatchRightUltra(ULTRASONIC_HATCH_RIGHT_CHANNEL),
                                     m_cargoLeftUltra(ULTRASONIC_CARGO_LEFT_CHANNEL),
                                     m_hatchLeftUltra(ULTRASONIC_HATCH_LEFT_CHANNEL), 
                                     m_jumper(ULTRASONIC_JUMPER_CHANNEL) {

}

void VisionSubsystem::robotInit() {

}

void VisionSubsystem::teleopInit() {

}

void VisionSubsystem::teleop() {

}

double VisionSubsystem::GetCargoUltraDistance() {
    double r = (m_cargoRightUltra.GetVoltage() / m_jumper.GetVoltage() / m_scale);
    double l = (m_cargoLeftUltra.GetVoltage() / m_jumper.GetVoltage() / m_scale);
    double v;
}

double VisionSubsystem::GetHatchUltraDistance() {
    double r = (m_hatchRightUltra.GetVoltage() / m_jumper.GetVoltage() / m_scale);
    double l = (m_hatchLeftUltra.GetVoltage() / m_jumper.GetVoltage() / m_scale);
    double v;
}