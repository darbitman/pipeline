#include "MergeChannels.hpp"

#include <memory>

#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

namespace sc
{
MergeChannels::MergeChannels() {}

MergeChannels::~MergeChannels() {}

void MergeChannels::runSeamCarverProcessor(BasePipelineData* pData)
{
    static_cast<VerticalSeamCarverData*>(pData)->mergeChannelsAndStoreToSavedImage();
}

}  // namespace sc
