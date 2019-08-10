#include "SeamRemover.hpp"

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
SeamRemover::SeamRemover() {}

SeamRemover::~SeamRemover() {}

void SeamRemover::runSeamCarverProcessor(shared_ptr<VerticalSeamCarverData> pData)
{
    // TODO
}

namespace
{
SeamCarverProcessorFactoryRegistration autoregister(EPipelineStageId::STAGE_3, []() {
    return dynamic_pointer_cast<ISeamCarverDataProcessor>(make_shared<SeamRemover>());
});
}

}  // namespace sc
