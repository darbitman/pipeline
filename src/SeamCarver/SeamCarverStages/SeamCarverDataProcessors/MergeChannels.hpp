#ifndef MERGECHANNELS_HPP
#define MERGECHANNELS_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class MergeChannels : public ISeamCarverDataProcessor
{
  public:
    MergeChannels();

    virtual ~MergeChannels();

    virtual void runSeamCarverProcessor(VerticalSeamCarverData* pData) override;

    // deleted to prevent misuse
    MergeChannels(const MergeChannels&) = delete;
    MergeChannels(MergeChannels&&) = delete;
    MergeChannels& operator=(const MergeChannels&) = delete;
    MergeChannels& operator=(MergeChannels&&) = delete;
};

}  // namespace sc

#endif
