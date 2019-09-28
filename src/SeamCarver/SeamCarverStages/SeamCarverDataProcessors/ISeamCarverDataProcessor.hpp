#pragma once

#include <memory>

#include "VerticalSeamCarverData.hpp"

namespace pipeline
{
class ISeamCarverDataProcessor
{
  public:
    virtual ~ISeamCarverDataProcessor();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) = 0;
};
}  // namespace pipeline
