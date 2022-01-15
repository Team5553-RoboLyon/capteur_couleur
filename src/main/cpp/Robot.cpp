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
  m_colorMatcher.AddColorMatch(kredBall);
  m_colorMatcher.AddColorMatch(kblueBall);
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
  /**
     * The method GetColor() returns a normalized color value from the sensor and can be
     * useful if outputting the color to an RGB LED or similar. To
     * read the raw color, use GetRawColor().
     * 
     * The color sensor works best when within a few inches from an object in
     * well lit conditions (the built in LED is a big help here!). The farther
     * an object is the more light from the surroundings will bleed into the 
     * measurements and make it difficult to accurately determine its color.
     */
  frc::Color detectedColor = m_colorSensor.GetColor();

  double proximity = m_colorSensor.GetProximity();
  frc::SmartDashboard::PutNumber("Proximity", proximity);
  /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);

  double IR = m_colorSensor.GetIR();
  frc::SmartDashboard::PutNumber("IR", IR);

  double confidence = 0.0;

  CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
  if (matchedColor == kGaffer)
  {
    frc::SmartDashboard::PutString("Detected Color", "Gaffer");
  }
  else if (matchedColor == kCarpet)
  {
    frc::SmartDashboard::PutString("Detected Color", "Carpet");
  }
  else if (matchedColor == kredBall)
  {
    frc::SmartDashboard::PutString("Detected Color", "Red Ball");
  }
  else if (matchedColor == kblueBall)
  {
    frc::SmartDashboard::PutString("Detected Color", "Blue Ball");
  }
  frc::SmartDashboard::PutNumber("Confidence", confidence);
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
