#pragma once

#include <cstdint>
#include <memory>

namespace pipeline
{
class IDataProcessor;

class DataProcessorManager
{
  public:
    DataProcessorManager() = default;

    virtual ~DataProcessorManager() = default;

    virtual void addNewDataProcessor(std::unique_ptr<IDataProcessor>& pDataProcessor,
                                     uint32_t stageNumber) noexcept;

    virtual void addNewDataProcessor(std::unique_ptr<IDataProcessor>&& pDataProcessor,
                                     uint32_t stageNumber) noexcept;

    virtual void deleteDataProcessor(uint32_t stageNumber) noexcept;

    virtual IDataProcessor* getDataProcessor(uint32_t stageNumber) const noexcept;

  private:
};

}  // namespace pipeline