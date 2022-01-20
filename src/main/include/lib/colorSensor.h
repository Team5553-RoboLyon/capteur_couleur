#include "rev/ColorSensorV3.h"

class CustomColorSensor
{
public:
    CustomColorSensor(int address);
    frc::Color getColor();
    double getIR();

private:
    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

    frc::I2C i2cMultiplexer = frc::I2C(frc::I2C::Port::kOnboard, 0x70);

    rev::ColorSensorV3 m_colorSensor{i2cPort};

    int addressOnMultiplexer;
};