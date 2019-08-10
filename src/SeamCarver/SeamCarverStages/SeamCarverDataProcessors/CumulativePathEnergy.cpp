#include "CumulativePathEnergy.hpp"

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
CumulativePathEnergy::CumulativePathEnergy() {}

CumulativePathEnergy::~CumulativePathEnergy() {}

void CumulativePathEnergy::runSeamCarverProcessor(VerticalSeamCarverData* pData)
{
    // TODO
}

namespace
{
SeamCarverProcessorFactoryRegistration autoregister(EPipelineStageId::STAGE_1, []() {
    return dynamic_pointer_cast<ISeamCarverDataProcessor>(make_shared<CumulativePathEnergy>());
});
}

}  // namespace sc
