// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "lib/ColorSensorMultiplexer.h"

ColorSensorMultiplexer::ColorSensorMultiplexer()
{
    for (int i = 0; i < 8; i++)
    {
        m_i2cMultiplexer.Write(0x70, 1 << i);
        m_colorSensors[i] = new rev::ColorSensorV3{frc::I2C::Port::kOnboard};
    }
}
ColorSensorMultiplexer::~ColorSensorMultiplexer()
{
    for (int i = 8; i > -1; i--)
    {
        m_i2cMultiplexer.Write(0x70, 1 << i);
        delete m_colorSensors[i];
    }
}

frc::Color ColorSensorMultiplexer::GetColor(int colorSensorId)
{
    m_i2cMultiplexer.Write(0x70, 1 << colorSensorId);
    frc::Color couleur = m_colorSensors[colorSensorId]->GetColor();
    m_i2cMultiplexer.Write(0x70, 1 << 0);
    return couleur;
}
double ColorSensorMultiplexer::GetIR(int colorSensorId)
{
    m_i2cMultiplexer.Write(0x70, 1 << colorSensorId);
    double ir = m_colorSensors[colorSensorId]->GetIR();
    m_i2cMultiplexer.Write(0x70, 1 << 0);
    return ir;
}