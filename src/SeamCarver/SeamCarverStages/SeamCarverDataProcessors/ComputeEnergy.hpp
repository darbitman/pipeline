#ifndef COMPUTEENERGY_HPP
#define COMPUTEENERGY_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"
using namespace std;
namespace sc
{
class ComputeEnergy : public ISeamCarverDataProcessor
{
  public:
    ComputeEnergy();

    virtual ~ComputeEnergy();

    virtual void runSeamCarverProcessor(VerticalSeamCarverData* pData) override;

    // deleted to prevent misuse
    ComputeEnergy(const ComputeEnergy&) = delete;
    ComputeEnergy(ComputeEnergy&&) = delete;
    ComputeEnergy& operator=(const ComputeEnergy&) = delete;
    ComputeEnergy& operator=(ComputeEnergy&&) = delete;
};



}  // namespace sc

#endif
