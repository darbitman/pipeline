#include "ComputeEnergy.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace sc
{
ComputeEnergy::ComputeEnergy() {}

ComputeEnergy::~ComputeEnergy() {}

void ComputeEnergy::runSeamCarverProcessor(VerticalSeamCarverData* pData)
{
    // TODO
}

namespace
{
SeamCarverProcessorFactoryRegistration autoregister(EPipelineStageId::STAGE_0, []() {
    return dynamic_pointer_cast<ISeamCarverDataProcessor>(make_shared<ComputeEnergy>());
});
}

}  // namespace sc
