#include "SeamRemover.hpp"

#include <memory>

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

}  // namespace sc
