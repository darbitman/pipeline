#ifndef ISEAMCARVERDATAPROCESSOR_HPP
#define ISEAMCARVERDATAPROCESSOR_HPP

#include <memory>

#include "VerticalSeamCarverData.hpp"

namespace sc
{
class ISeamCarverDataProcessor
{
  public:
    virtual ~ISeamCarverDataProcessor();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) = 0;
};
}  // namespace sc

#endif
