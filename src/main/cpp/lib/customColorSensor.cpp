#include "lib/customColorSensor.h"
#include <iostream>

CustomColorSensor::CustomColorSensor(int address)
{
    m_addressOnMultiplexer = address;
    m_i2cMultiplexer.Write(0x70, 1 << m_addressOnMultiplexer);
    m_colorSensor = new rev::ColorSensorV3{frc::I2C::Port::kOnboard};
    m_i2cMultiplexer.Write(0x70, 1 << 0);
}

CustomColorSensor::~CustomColorSensor()
{
    m_i2cMultiplexer.Write(0x70, 1 << m_addressOnMultiplexer);
    delete m_colorSensor;
    m_i2cMultiplexer.Write(0x70, 1 << 0);
}

frc::Color CustomColorSensor::GetColor()
{
    m_i2cMultiplexer.Write(0x70, 1 << m_addressOnMultiplexer);
    frc::Color couleur = m_colorSensor->GetColor();
    m_i2cMultiplexer.Write(0x70, 1 << 0);
    return couleur;
}

double CustomColorSensor::GetIR()
{
    m_i2cMultiplexer.Write(0x70, 1 << m_addressOnMultiplexer);
    double ir = m_colorSensor->GetIR();
    m_i2cMultiplexer.Write(0x70, 1 << 0);

    return ir;
}
