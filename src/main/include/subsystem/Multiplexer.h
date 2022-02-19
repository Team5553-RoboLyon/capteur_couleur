// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/I2C.h>
#include <cassert>
#include <iostream>

class Multiplexer
{
public:
  Multiplexer(int sensor_number);
  ~Multiplexer();
  void SetPosition();
  void ResetPosition();

private:
  frc::I2C m_i2cMultiplexer = frc::I2C(frc::I2C::Port::kMXP, 0x70);
  int m_sensor_number;
  static inline bool m_sensors[7];
};
