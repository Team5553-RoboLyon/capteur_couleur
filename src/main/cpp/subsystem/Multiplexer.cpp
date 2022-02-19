// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Multiplexer.h"

Multiplexer::Multiplexer(int sensor_number)
{
    m_sensor_number = sensor_number;
    assert(!m_sensors[m_sensor_number] && "le bus du multiplexer est déja reservé");
    Multiplexer::m_sensors[m_sensor_number] = true;
}
Multiplexer::~Multiplexer()
{
    m_sensors[m_sensor_number] = false;
}

void Multiplexer::SetPosition()
{
    m_i2cMultiplexer.Write(0x70, 1 << m_sensor_number);
}
void Multiplexer::ResetPosition()
{
    m_i2cMultiplexer.Write(0x70, 1 << 0);
}
