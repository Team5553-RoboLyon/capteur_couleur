// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "lib/colorMatch.h"
#include "rev/ColorSensorV3.h"
#include "lib/customColorSensor.h"
#include "lib/ColorSensorMultiplexer.h"
#include <frc/Timer.h>

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  // CustomColorSensor m_colorSensor2 = CustomColorSensor(2);
  // CustomColorSensor m_colorSensor3 = CustomColorSensor(3);
  ColorSensorMultiplexer m_colorSensorMultiplexer;

  ColorMatch m_colorMatcher;

  static constexpr CustomColor kGaffer = CustomColor(0.255, 0.476, 0.268, 12);
  static constexpr CustomColor kCarpet = CustomColor(0.250, 0.470, 0.270, 28);
  static constexpr CustomColor kredBall = CustomColor(0.412, 0.410, 0.200, 35);
  static constexpr CustomColor kblueBall = CustomColor(0.191, 0.437, 0.367, 27);

  frc::Timer m_timer;
  double last_time;
};
