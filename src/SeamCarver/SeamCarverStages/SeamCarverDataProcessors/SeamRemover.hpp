#ifndef SEAMREMOVER_HPP
#define SEAMREMOVER_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class SeamRemover : public ISeamCarverDataProcessor
{
  public:
    SeamRemover();

    virtual ~SeamRemover();

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    SeamRemover(const SeamRemover&) = delete;
    SeamRemover(SeamRemover&&) = delete;
    SeamRemover& operator=(const SeamRemover&) = delete;
    SeamRemover& operator=(SeamRemover&&) = delete;
};

}  // namespace sc

#endif
