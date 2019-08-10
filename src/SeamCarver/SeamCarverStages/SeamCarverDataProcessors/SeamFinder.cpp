#include "SeamFinder.hpp"

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
SeamFinder::SeamFinder() {}

SeamFinder::~SeamFinder() {}

void SeamFinder::runSeamCarverProcessor(VerticalSeamCarverData* pData)
{
    // TODO
}

namespace
{
SeamCarverProcessorFactoryRegistration autoregister(EPipelineStageId::STAGE_2, []() {
    return dynamic_pointer_cast<ISeamCarverDataProcessor>(make_shared<SeamFinder>());
});
}

}  // namespace sc
