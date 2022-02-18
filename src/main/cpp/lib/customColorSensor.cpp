#include "lib/customColorSensor.h"
#include <iostream>

CustomColorSensor::CustomColorSensor(int address)
{
    std::cout << "multiplexer definition : " << address << std::endl;
    m_multiplexer = new Multiplexer(address);
    std::cout << "multiplexer created" << std::endl;
    m_multiplexer->SetPosition();
    std::cout << "position seted" << std::endl;
    // m_colorSensor = new rev::ColorSensorV3{frc::I2C::Port::kOnboard};
    std::cout << "color sensor created" << std::endl;
    m_multiplexer->ResetPosition();
}

CustomColorSensor::~CustomColorSensor()
{
    m_multiplexer->SetPosition();
    delete m_colorSensor;
    m_multiplexer->ResetPosition();
}

frc::Color CustomColorSensor::GetColor()
{
    m_multiplexer->SetPosition();
    frc::Color couleur = m_colorSensor->GetColor();
    m_multiplexer->ResetPosition();
    return couleur;
}

double CustomColorSensor::GetProximity()
{
    m_multiplexer->SetPosition();
    double proximity = m_colorSensor->GetProximity();
    m_multiplexer->ResetPosition();
    return proximity;
}

double CustomColorSensor::GetIR()
{
    m_multiplexer->SetPosition();
    double ir = m_colorSensor->GetIR();
    m_multiplexer->ResetPosition();
    return ir;
}
