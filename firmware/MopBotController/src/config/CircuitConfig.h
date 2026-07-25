#pragma once

namespace CircuitConfig {
    constexpr float MOT_CURRENT_SENSE_RESISTANCE = 1800.0f;                 // Resistance in ohms for current sense resistor
    constexpr float MOT_CURRENT_SENSE_CONVERSION_FACTOR = 0.000377f;        // Conversion factor for the LMD18200T Motorcontroller
    constexpr float ADC_REFERENCE = 5.0f;                                   // Reference voltage for ADC conversion
    constexpr float ADC_MAX = 1023.0f;                                      // Maximum value for ADC conversion
}