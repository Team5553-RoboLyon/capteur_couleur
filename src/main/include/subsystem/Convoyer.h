// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "lib/customColorSensor.h"
#include "lib/colorMatch.h"
#include "Constant.h"

class Convoyer
{
public:
  Convoyer();
  bool isBall();
  int ballType();

private:
  CustomColorSensor m_leftColorSensor = CustomColorSensor(LEFT_CONVOYER_COLOR_SENSOR);
  CustomColorSensor m_rightColorSensor = CustomColorSensor(RIGHT_CONVOYER_COLOR_SENSOR);
  ColorMatch m_colorMatcher;
  static constexpr CustomColor kredBall = CustomColor(0.412, 0.410, 0.200, 35);
  static constexpr CustomColor kblueBall = CustomColor(0.191, 0.437, 0.367, 27);
};
