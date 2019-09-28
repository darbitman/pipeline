#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

#include "IPipelineStage.hpp"
#include "PipelineIdentifiers.hpp"

namespace pipeline
{
class PipelineSenderReceiver;
class IMessageRouter;
class IDataProcessor;
class PipelineMessageBase;
class PipelineDataBase;

class PipelineStageBase : public IPipelineStage
{
  public:
    /// @brief Builds a component
    /// @param thisComponentId Unique identifier for this component (akin to an IP)
    /// @param componentLinkType What medium shall the messages be transported on
    /// @param pDataProcessor Reference to an object that will process the data
    /// @param pMessageRouter Reference to an implementation of an IMessageRouter that will be used
    /// for sending and receiving messages between components.
    explicit PipelineStageBase(uint32_t thisComponentId, uint32_t componentLinkType,
                               IDataProcessor* pDataProcessor, IMessageRouter* pMessageRouter);

    /// @brief Destructor will stop the thread if it needs to be stopped and unregisters itself with
    /// the IMessageRouter instance.
    virtual ~PipelineStageBase() override;

    /// @brief This method start the thread that will receive incoming messages and pass them onto
    /// their appropriate handlers. This method will fail to start the thread if the pDataProcessor
    /// or pMessageRouter pointers are nullptr, since those are required components.
    virtual void runComponent() override;

    /// @brief This method stops the thread that receives incoming messages
    virtual void stopComponent() override;

    /// @brief Returns the status of the thread
    /// @return bool
    virtual bool isComponentRunning() const noexcept override;

    /// Deleted to prevent misuse
    PipelineStageBase(const PipelineStageBase&) = delete;
    PipelineStageBase(PipelineStageBase&&) = delete;
    PipelineStageBase& operator=(const PipelineStageBase&) = delete;
    PipelineStageBase& operator=(PipelineStageBase&&) = delete;

  private:
    void incomingMessageThread();

    void doStopStage();

    const uint32_t thisComponentId_;

    const uint32_t componentLinkType_;

    /// Flag to start and stop the thread, and to keep track if it's running
    std::atomic<bool> bThreadIsRunning_;

    /// Inidicates whether the thread has joined
    bool bThreadHasJoined_;

    /// This PipelineStageBase does not own this pointer so it's not responsible for its deletion.
    /// This is used for sending/receiving messages between components
    IMessageRouter* pMessageRouter_{nullptr};

    /// This PipelineStageBase does not own this pointer so it's not responsible for its deletion.
    /// A reference to the object that will process the data that comes in
    IDataProcessor* pDataProcessor_{nullptr};

    std::thread dataProcessorThread_;
};

}  // namespace pipeline
