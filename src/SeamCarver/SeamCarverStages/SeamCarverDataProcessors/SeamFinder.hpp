#ifndef SEAMFINDER_HPP
#define SEAMFINDER_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class SeamFinder : public ISeamCarverDataProcessor
{
  public:
    SeamFinder();

    virtual ~SeamFinder();

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    SeamFinder(const SeamFinder&) = delete;
    SeamFinder(SeamFinder&&) = delete;
    SeamFinder& operator=(const SeamFinder&) = delete;
    SeamFinder& operator=(SeamFinder&&) = delete;
};

}  // namespace sc

#endif
