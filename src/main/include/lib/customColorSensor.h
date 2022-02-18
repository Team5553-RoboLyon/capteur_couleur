#pragma once

#include "rev/ColorSensorV3.h"
#include "subsystem/Multiplexer.h"

class CustomColorSensor
{
public:
    CustomColorSensor(int address);
    ~CustomColorSensor();
    frc::Color GetColor();
    double GetIR();
    double GetProximity();

private:
    Multiplexer *m_multiplexer;
    rev::ColorSensorV3 *m_colorSensor;
};