#include "rev/ColorSensorV3.h"

class CustomColorSensor
{
public:
    CustomColorSensor(int address);
    ~CustomColorSensor();
    frc::Color GetColor();
    double GetIR();

private:
    frc::I2C m_i2cMultiplexer = frc::I2C(frc::I2C::Port::kOnboard, 0x70);

    rev::ColorSensorV3 *m_colorSensor;

    int m_addressOnMultiplexer;
};