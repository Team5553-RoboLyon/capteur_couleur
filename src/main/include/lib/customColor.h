#pragma once

#include <algorithm>

class CustomColor
{
public:
    /**
   * Constructs a Color.
   *
   * @param red Red value (0-1)
   * @param green Green value (0-1)
   * @param blue Blue value (0-1)
   */
    constexpr CustomColor(double r, double g, double b, double i)
        : red(roundAndClamp(r)),
          green(roundAndClamp(g)),
          blue(roundAndClamp(b)),
          infraRed(roundAndClamp(i / 255.0f)) {}

    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    double infraRed = 0.0;

private:
    static constexpr double kPrecision = 1.0 / (1 << 12);

    static constexpr double roundAndClamp(double value)
    {
        const auto rounded =
            (static_cast<int>(value / kPrecision) + 0.5) * kPrecision;
        return std::clamp(rounded, 0.0, 1.0);
    }
};

inline bool operator==(const CustomColor &c1, const CustomColor &c2)
{
    return c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue && c1.infraRed == c2.infraRed;
}

inline bool operator!=(const CustomColor &c1, const CustomColor &c2)
{
    return !(c1 == c2);
}