// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/customColorSensor.h"
#include "lib/colorMatch.h"
#include "Constant.h"

enum States
{
  do_nothing,
  tape_approach,
  left_reached,
  right_reached,
  line_reached,
  surely_on_line,
};

class LineDetector
{
public:
  LineDetector();
  bool isOnLine();
  bool isLeftOnLine();
  bool isRightOnLine();
  void position();
  void autoPositionMode(bool newMode);

private:
  CustomColorSensor m_leftColorSensor = CustomColorSensor(LEFT_LINE_COLOR_SENSOR);
  CustomColorSensor m_rightColorSensor = CustomColorSensor(RIGHT_LINE_COLOR_SENSOR);
  ColorMatch m_colorMatcher;
  static constexpr CustomColor kGaffer = CustomColor(0.252454969618056, 0.486187274639423, 0.261445545014881, 10.8);
  static constexpr CustomColor kCarpet = CustomColor(0.250, 0.470, 0.270, 28);
  int oneLineCount = 0;
  States state = States::do_nothing;
};
