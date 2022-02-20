#include "subsystem/LineDetector.h"

LineDetector::LineDetector()
{
    m_colorMatcher.AddColorMatch(kGaffer);
    m_colorMatcher.AddColorMatch(kCarpet);

    m_leftMotor.RestoreFactoryDefaults();
    m_leftMotorFollower.RestoreFactoryDefaults();
    m_rightMotor.RestoreFactoryDefaults();
    m_rightMotorFollower.RestoreFactoryDefaults();

    m_leftMotorFollower.Follow(m_leftMotor);
    m_rightMotorFollower.Follow(m_rightMotor);

    m_leftMotor.SetInverted(false);
    m_leftMotorFollower.SetInverted(false);
    m_rightMotor.SetInverted(true);
    m_rightMotorFollower.SetInverted(true);

    m_leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_leftMotorFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    m_rightMotorFollower.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
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
    std::cout << isLeftOnLine() << ":" << isRightOnLine() << std::endl;
    frc::SmartDashboard::PutNumber("state", state);
    switch (state)
    {
    case States::tape_approach:
        if (!isLeftOnLine() && !isRightOnLine())
        {
            m_leftMotor.Set(0.1);
            m_rightMotor.Set(0.1);
        }
        else if (isLeftOnLine())
        {
            m_leftMotor.Set(0);
            m_rightMotor.Set(0);
            state = States::left_reached;
        }
        else if (isRightOnLine())
        {
            m_leftMotor.Set(0);
            m_rightMotor.Set(0);
            state = States::right_reached;
        }
        break;

    case States::left_reached:
        if (!isLeftOnLine())
        {
            m_leftMotor.Set(-0.075);
            m_rightMotor.Set(0.0);
        }
        else if (!isRightOnLine())
        {
            m_rightMotor.Set(0.075);
            m_leftMotor.Set(0.0);
        }
        else
        {
            oneLineCount = 0;
            state = States::line_reached;
        }
        break;
    case States::right_reached:
        if (!isRightOnLine())
        {
            m_leftMotor.Set(0.0);
            m_rightMotor.Set(-0.075);
        }
        else if (!isLeftOnLine())
        {
            m_leftMotor.Set(0.075);
            m_rightMotor.Set(0.0);
        }
        else
        {
            oneLineCount = 0;
            state = States::line_reached;
        }
        break;

    case States::line_reached:
        // assert(false && "LineReached");
        m_leftMotor.Set(0.0);
        m_rightMotor.Set(0.0);
        oneLineCount++;
        if (isOnLine())
        {
            if (oneLineCount > 20)
            {
                state = States::surely_on_line;
                frc::SmartDashboard::PutString("action", "arrive");
            }
        }
        else
        {
            oneLineCount = 0;
            state = States::tape_approach;
        }
    case States::do_nothing:
        m_rightMotor.Set(0.0);
        m_leftMotor.Set(0.0);
        break;
    default:
        break;
    }
}

void LineDetector::autoPositionMode(bool newMode)
{
    state = newMode ? States::tape_approach : States::do_nothing;
}