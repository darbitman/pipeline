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

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) = 0;
};
}  // namespace sc

#endif
