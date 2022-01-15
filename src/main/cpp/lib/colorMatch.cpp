/*
 * Copyright (c) 2020 REV Robotics
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of REV Robotics nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "lib/ColorMatch.h"

#include <algorithm>
#include <cmath>
#include "lib/customColor.h"

static constexpr double kDefaultConfidence = 0.95;

static double CalculateDistance(const CustomColor &color1, const CustomColor &color2)
{
    double redDiff = color1.red - color2.red;
    double greenDiff = color1.green - color2.green;
    double blueDiff = color1.blue - color2.blue;
    double infDiff = color1.infraRed - color2.infraRed;

    return std::sqrt((redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff + infDiff * infDiff) / 2);
}

ColorMatch::ColorMatch() : m_confidenceLevel(kDefaultConfidence) {}

void ColorMatch::AddColorMatch(const CustomColor &color)
{
    m_colorsToMatch.push_back(color);
}

void ColorMatch::SetConfidenceThreshold(double confidence)
{
    m_confidenceLevel = std::clamp(confidence, 0.0, 1.0);
}

std::optional<CustomColor> ColorMatch::MatchColor(const CustomColor &colorToMatch)
{
    double d;
    return MatchColor(colorToMatch, d);
}

std::optional<CustomColor> ColorMatch::MatchColor(const CustomColor &colorToMatch, double &confidence)
{
    CustomColor color = MatchClosestColor(colorToMatch, confidence);
    if (confidence > m_confidenceLevel)
    {
        return color;
    }
    confidence = 0.0;
    return {};
}

CustomColor ColorMatch::MatchClosestColor(const CustomColor &color, double &confidence)
{
    double magnitude = (color.red + color.blue + color.green + color.infraRed) / 2.0f;

    if (magnitude > 0.0 && m_colorsToMatch.size() > 0)
    {
        double minDistance = 1.0; //peut etre deux ou un a checker
        int idx = 0;

        for (int i = 0; i < static_cast<int>(m_colorsToMatch.size()); i++)
        {
            double targetDistance = CalculateDistance(m_colorsToMatch[i], color);

            if (targetDistance < minDistance)
            {
                minDistance = targetDistance;
                idx = i;
            }
        }
        confidence = 1.0 - (minDistance / magnitude);
        return m_colorsToMatch[idx];
    }
    else
    {
        confidence = 0.0;
        return CustomColor(0, 0, 0, 0);
    }
}