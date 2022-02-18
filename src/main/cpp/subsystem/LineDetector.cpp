#include "subsystem/LineDetector.h"

LineDetector::LineDetector()
{
    m_colorMatcher.AddColorMatch(kGaffer);
    m_colorMatcher.AddColorMatch(kCarpet);
}

bool LineDetector::isOnLine()
{
    return isLeftOnLine() && isRightOnLine();
}
bool LineDetector::isLeftOnLine()
{
    // frc::Color detectedColor = m_leftColorSensor.GetColor();
    // double IR = m_leftColorSensor.GetIR();
    // double confidence;
    // CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
    // return matchedColor == kGaffer;
}
bool LineDetector::isRightOnLine()
{
    frc::Color detectedColor = m_rightColorSensor.GetColor();
    double IR = m_rightColorSensor.GetIR();
    double confidence;
    CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
    return matchedColor == kGaffer;
}

void LineDetector::mesureColor()
{
    frc::Color detectedColor = m_rightColorSensor.GetColor();

    frc::SmartDashboard::PutNumber("Red 2 ", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green 2 ", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue 2 ", detectedColor.blue);

    double IR = m_rightColorSensor.GetIR();

    frc::SmartDashboard::PutNumber("IR 2 ", IR);

    detectedColor = m_rightColorSensor.GetColor();
    frc::SmartDashboard::PutNumber("Red 3 ", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green 3 ", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue 3 ", detectedColor.blue);

    IR = m_rightColorSensor.GetIR();
    frc::SmartDashboard::PutNumber("IR 3 ", IR);
}