// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystem/Convoyer.h"

Convoyer::Convoyer()
{
    m_colorMatcher.AddColorMatch(kredBall);
    m_colorMatcher.AddColorMatch(kblueBall);
}

bool Convoyer::isBall()
{
    return ((m_leftColorSensor.GetProximity() < 100) && (m_rightColorSensor.GetProximity() < 100)); // TODO change < 100
}
int Convoyer::ballType()
{
    frc::Color detectedLeftColor = m_leftColorSensor.GetColor();
    frc::Color detectedRightColor = m_rightColorSensor.GetColor();
    double leftIR = m_leftColorSensor.GetIR();
    double rightIR = m_rightColorSensor.GetIR();

    double leftConfidence;
    double rightConfidence;
    CustomColor leftMatchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedLeftColor.red, detectedLeftColor.green, detectedLeftColor.blue, leftIR), leftConfidence);
    CustomColor rightMatchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedRightColor.red, detectedRightColor.green, detectedRightColor.blue, rightIR), rightConfidence);
    if (leftMatchedColor == rightMatchedColor)
    {
        if (leftMatchedColor == kredBall)
        {
            return 0;
        }
        else if (leftMatchedColor == kblueBall)
        {
            return 1;
        }
    }
    return -1;
}