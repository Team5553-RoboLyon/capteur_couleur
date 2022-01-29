// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "rev/ColorSensorV3.h"

class ColorSensorMultiplexer
{
public:
  ColorSensorMultiplexer();
  ~ColorSensorMultiplexer();
  frc::Color GetColor(int colorSensorId);
  double GetIR(int colorSensorId);

private:
  frc::I2C m_i2cMultiplexer = frc::I2C(frc::I2C::Port::kOnboard, 0x70);
  rev::ColorSensorV3 *m_colorSensors[7];
};
