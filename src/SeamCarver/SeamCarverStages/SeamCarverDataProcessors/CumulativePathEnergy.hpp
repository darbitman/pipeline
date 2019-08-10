#ifndef CUMULATIVEPATHENERGY_HPP
#define CUMULATIVEPATHENERGY_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class CumulativePathEnergy : public ISeamCarverDataProcessor
{
  public:
    CumulativePathEnergy();

    virtual ~CumulativePathEnergy();

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    CumulativePathEnergy(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy(CumulativePathEnergy&&) = delete;
    CumulativePathEnergy& operator=(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy& operator=(CumulativePathEnergy&&) = delete;
};

}  // namespace sc

#endif
