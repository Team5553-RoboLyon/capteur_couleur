// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/customColorSensor.h"
#include "lib/colorMatch.h"
#include "Constant.h"
class LineDetector
{
public:
  LineDetector();
  bool isOnLine();
  bool isLeftOnLine();
  bool isRightOnLine();
  void mesureColor();

private:
  // CustomColorSensor m_leftColorSensor = CustomColorSensor(LEFT_LINE_COLOR_SENSOR);
  CustomColorSensor m_rightColorSensor = CustomColorSensor(RIGHT_LINE_COLOR_SENSOR);
  ColorMatch m_colorMatcher;
  static constexpr CustomColor kGaffer = CustomColor(0.255, 0.476, 0.268, 12);
  static constexpr CustomColor kCarpet = CustomColor(0.250, 0.470, 0.270, 28);
};
