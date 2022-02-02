// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_colorMatcher.AddColorMatch(kCarpet);
  m_colorMatcher.AddColorMatch(kGaffer);
  // m_colorMatcher.AddColorMatch(kredBall);
  // m_colorMatcher.AddColorMatch(kblueBall);

  // m_timer.Start();
  // last_time = m_timer.Get();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{

  // frc::Color detectedColor = m_colorSensor2.GetColor();
  frc::Color detectedColor = m_colorSensorMultiplexer.GetColor(2);

  frc::SmartDashboard::PutNumber("Red 2 ", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green 2 ", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue 2 ", detectedColor.blue);

  // double IR = m_colorSensor2.GetIR();
  double IR = m_colorSensorMultiplexer.GetIR(2);

  frc::SmartDashboard::PutNumber("IR 2 ", IR);

  // detectedColor = m_colorSensor3.GetColor();
  detectedColor = m_colorSensorMultiplexer.GetColor(3);
  frc::SmartDashboard::PutNumber("Red 3 ", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green 3 ", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue 3 ", detectedColor.blue);

  // IR = m_colorSensor3.GetIR();
  IR = m_colorSensorMultiplexer.GetIR(3);
  frc::SmartDashboard::PutNumber("IR 3 ", IR);

  // double confidence = 0.0;

  // CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
  // if (matchedColor == kGaffer)
  // {
  //   frc::SmartDashboard::PutString("Detected Color", "Gaffer");
  // }
  // else if (matchedColor == kCarpet)
  // {
  //   frc::SmartDashboard::PutString("Detected Color", "Carpet");
  // }
  // else if (matchedColor == kredBall)
  // {
  //   frc::SmartDashboard::PutString("Detected Color", "Red Ball");
  // }
  // else if (matchedColor == kblueBall)
  // {
  //   frc::SmartDashboard::PutString("Detected Color", "Blue Ball");
  // }
  // frc::SmartDashboard::PutNumber("Confidence", confidence);
}

void Robot::AutonomousInit()
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic()
{
  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
