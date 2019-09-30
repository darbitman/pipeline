#pragma once

#include "IPipelineBuilder.hpp"

#include <memory>
#include <vector>

namespace pipeline
{
class IPipelineStage;
class IMessageRouter;
class DataProcessorManager;

class DefaultPipelineBuilder : public IPipelineBuilder
{
  public:
    explicit DefaultPipelineBuilder(DataProcessorManager* pDataProcessorManager,
                                    IMessageRouter* pMessageRouter) noexcept;

    virtual ~DefaultPipelineBuilder() = default;

    virtual void addNewComponent(uint32_t stageNumber) noexcept override;

    /// @brief Returns a 2D vector of pointers to IPipelineStage objects
    /// @return const std::vector<const std::vector<const std::unique_ptr<IPipelineStage>>>&
    /// First dimension is the particular stage in the pipeline
    /// Second dimension is the number of parallel components
    const std::vector<std::vector<std::unique_ptr<IPipelineStage>>>& getStages() const noexcept;

    /// @brief Returns a vector of parallel components for some stageNumber
    /// @param stageNumber
    /// @throw std::out_of_range if no components exist at stageNumber
    const std::vector<std::unique_ptr<IPipelineStage>>& getParallelComponents(
        uint32_t stageNumber) const;

    /// @brief Returns the number of stages
    /// @return size_t
    size_t getNumberOfStages() const noexcept;

    size_t getNumberOfParallelComponents(uint32_t stageNumber) const noexcept;

  private:
    /// @throw std::out_of_range If need to add a vector for the parallel stages
    void addTheNewComponent(uint32_t stageNumber, std::unique_ptr<IPipelineStage>& pStageToAdd);

    std::vector<std::vector<std::unique_ptr<IPipelineStage>>> pipeline_;

    DataProcessorManager* pDataProcessorManager_;

    IMessageRouter* pMessageRouter_;
};

}  // namespace pipeline
