#pragma once

#include <cstdint>
#include <memory>

#include "PipelineIdentifiers.hpp"

namespace pipeline
{
/// Forward Declarations
class BasePipelineData;

class PipelineMessageBase
{
  public:
    /// @brief constructor
    /// @param source
    /// @param destination
    /// @param messageType
    PipelineMessageBase(uint32_t source, uint32_t destination, uint32_t messageType,
                        uint32_t messageNumber);

    /// @brief destructor
    virtual ~PipelineMessageBase() = default;

    inline virtual void setSource(uint32_t source) noexcept final { source_ = source; }

    inline virtual uint32_t getSource() const noexcept final { return source_; }

    inline virtual void setDestination(uint32_t destination) noexcept final
    {
        destination_ = destination;
    }

    inline virtual uint32_t getDestination() const noexcept final { return destination_; }

    inline virtual void setMessageNumber(uint32_t messageNumber) noexcept final
    {
        messageNumber_ = messageNumber;
    }

    inline virtual uint32_t getMessageNumber() const noexcept final { return messageNumber_; }

    inline virtual uint32_t getMessageType() const noexcept final { return messageType_; }

    /// @brief Set the owner of the data to this PipelineMessageBase
    /// @param pPipelineData
    /// Since the argument is passed by reference, the original unique_ptr will be nullptr since
    virtual void setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) noexcept = 0;

    /// @brief Returns a reference to the data this message owns
    /// @return std::unique_ptr<BasePipelineData>&
    virtual std::unique_ptr<BasePipelineData>& getOwnedData() noexcept = 0;

    /// @brief Releases ownership of the data this message owns and return a pointer to it
    /// @return BasePipelineData* This can return a nullptr
    virtual BasePipelineData* releaseOwnedData() noexcept = 0;

    /// @brief Deletes the data this message owns
    virtual void deleteOwnedData() noexcept = 0;

    /// Deleted to prevent misuse
    PipelineMessageBase(const PipelineMessageBase&) = delete;
    PipelineMessageBase(const PipelineMessageBase&&) = delete;
    PipelineMessageBase& operator=(const PipelineMessageBase&) = delete;
    PipelineMessageBase& operator=(const PipelineMessageBase&&) = delete;

  private:
    uint32_t source_;

    uint32_t destination_;

    uint32_t messageType_;

    uint32_t messageNumber_;
};

}  // namespace pipeline
