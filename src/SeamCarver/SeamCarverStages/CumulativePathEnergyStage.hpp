#ifndef CUMULATIVEPATHENERGYSTAGE_HPP
#define CUMULATIVEPATHENERGYSTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class CumulativePathEnergyStage : public BasePipelineStage
{
public:
    explicit CumulativePathEnergyStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~CumulativePathEnergyStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    CumulativePathEnergyStage(const CumulativePathEnergyStage&) = delete;
    CumulativePathEnergyStage(const CumulativePathEnergyStage&&) = delete;
    CumulativePathEnergyStage& operator=(const CumulativePathEnergyStage&) =
        delete;
    CumulativePathEnergyStage& operator=(const CumulativePathEnergyStage&&) =
        delete;

protected:
    /**
     * @brief method that does the actual data processing
     * calls calculateCumulativePathEnergy
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData) override;

private:
    void calculateCumulativePathEnergy(VerticalSeamCarverData* pData);
};
}  // namespace sc

#endif
