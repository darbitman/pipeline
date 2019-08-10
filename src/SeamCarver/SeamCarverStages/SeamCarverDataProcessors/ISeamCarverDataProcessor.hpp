#ifndef ISEAMCARVERDATAPROCESSOR_HPP
#define ISEAMCARVERDATAPROCESSOR_HPP

#include "VerticalSeamCarverData.hpp"

namespace sc
{
class ISeamCarverDataProcessor
{
  public:
    virtual ~ISeamCarverDataProcessor();

    virtual void runSeamCarverProcessor(VerticalSeamCarverData* pData) = 0;
};
}  // namespace sc

#endif
