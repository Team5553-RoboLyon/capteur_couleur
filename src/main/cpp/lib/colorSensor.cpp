#include "lib/colorSensor.h"

CustomColorSensor::CustomColorSensor(int address)
{
    addressOnMultiplexer = address;
}

frc::Color CustomColorSensor::getColor()
{
    i2cMultiplexer.Write(0x70, 1 << addressOnMultiplexer);
    frc::Color couleur = m_colorSensor.GetColor();
    i2cMultiplexer.Write(0x70, 1 << 0);
    return couleur;
}

double CustomColorSensor::getIR()
{
    return m_colorSensor.GetIR();
}