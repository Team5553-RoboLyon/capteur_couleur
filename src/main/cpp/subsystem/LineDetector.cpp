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