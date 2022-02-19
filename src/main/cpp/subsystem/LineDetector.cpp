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
    frc::Color detectedColor = m_leftColorSensor.GetColor();
    double IR = m_leftColorSensor.GetIR();
    double confidence;
    CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
    return matchedColor == kGaffer;
}
bool LineDetector::isRightOnLine()
{
    frc::Color detectedColor = m_rightColorSensor.GetColor();
    double IR = m_rightColorSensor.GetIR();
    double confidence;
    CustomColor matchedColor = m_colorMatcher.MatchClosestColor(CustomColor(detectedColor.red, detectedColor.green, detectedColor.blue, IR), confidence);
    return matchedColor == kGaffer;
}

void LineDetector::position(/*drivetrain*/)
{
    switch (state)
    {
    case States::tape_approach:
        if (!isLeftOnLine() && !isRightOnLine())
        {
            frc::SmartDashboard::PutString("action", "avance");
        }
        else if (isLeftOnLine())
        {
            state = States::left_reached;
        }
        else if (isRightOnLine())
        {
            state = States::right_reached;
        }
        break;

    case States::left_reached:
        if (!isLeftOnLine())
        {
            frc::SmartDashboard::PutString("action", "avance la droite");
        }
        else if (!isRightOnLine())
        {
            frc::SmartDashboard::PutString("action", "avance la gauche");
        }
        else
        {
            state = States::line_reached;
            frc::SmartDashboard::PutString("action", "arrive");
        }
        break;
    case States::right_reached:
        if (!isRightOnLine())
        {
            frc::SmartDashboard::PutString("action", "avance la gauche");
        }
        else if (!isLeftOnLine())
        {
            frc::SmartDashboard::PutString("action", "avance la droite");
        }
        else
        {
            state = States::line_reached;
        }
        break;

    case States::line_reached:
        oneLineCount++;
        if (oneLineCount > 20)
        {
            state = States::surely_on_line;
            frc::SmartDashboard::PutString("action", "arrive");
        }
    default:
        break;
    }
}

void LineDetector::autoPositionMode(bool newMode)
{
    state = States::tape_approach;
}