#pragma once

#include <cstdint>

namespace seamcarver
{
using PixelColorType = uint16_t;
using PixelEnergyType = uint16_t;
using PixelColumnType = int32_t;
using SignedPixelEnergyType = int16_t;

static constexpr PixelEnergyType MAXIMUM_ENERGY{0xFFFF};

}  // namespace seamcarver
