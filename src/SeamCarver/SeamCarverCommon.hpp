#pragma once

#include <cstdint>

namespace seamcarver
{
using PixelColorType = uint16_t;

using PixelEnergyType = uint32_t;
using SignedPixelEnergyType = int32_t;

using PixelColumnType = int32_t;

static constexpr PixelEnergyType MAXIMUM_ENERGY{0xFFFFFFFF};

}  // namespace seamcarver
