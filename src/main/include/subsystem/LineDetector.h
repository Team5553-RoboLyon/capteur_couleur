// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/customColorSensor.h"
#include "lib/colorMatch.h"
#include "Constant.h"
#include <rev/CANSparkMax.h>

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
  CustomColorSensor m_leftColorSensor = CustomColorSensor(LEFT_LINE_COLOR_SENSOR);
  CustomColorSensor m_rightColorSensor = CustomColorSensor(RIGHT_LINE_COLOR_SENSOR);

private:
  ColorMatch m_colorMatcher;
  static constexpr CustomColor kGaffer = CustomColor(0.2559814453125, 0.4898681640625, 0.2545166015625, 4.8);
  static constexpr CustomColor kCarpet = CustomColor(0.2811279296875, 0.4918212890625, 0.2269287109375, 7);
  int oneLineCount = 0;
  States state = States::do_nothing;
  rev::CANSparkMax m_leftMotor{3, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorFollower{4, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorFollower{2, rev::CANSparkMax::MotorType::kBrushless};
};
