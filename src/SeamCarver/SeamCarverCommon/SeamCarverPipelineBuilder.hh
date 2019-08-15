#ifndef SEAMCARVERPIPELINEBUILDER_HPP
#define SEAMCARVERPIPELINEBUILDER_HPP

#include <vector>

#include "pipelineconfigurationtype.hpp"
#include "pipelinestages.hpp"
#include "seamcarverpipelineinterface.hpp"
#include "seamcarverqueuemanager.hpp"
#include "seamcarversendrcvmgr.hpp"
#include "seamcarverstage.hpp"
#include "sharedqueue.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
/// Client calls the contructor with PipelineConfigurationType
/// Client then makes the following calls to START the pipeline
///     1. Call initialize() to initialize the stages
///
///     2. Call runPipelineStages
///
///     3. Call createPipelineInterface() to get a SeamCarverPipelineInterface which allows the
///     client to insert new frames into the pipeline for processing
///
///     4. Use the SeamCarverPipelineInterface object to add new frames for processing and to get
///     the results
///
/// Client can call addNewPipelineStage() to add an additional stage to speed up processing multiple
/// frames in parallel. It can only be called after the pipeline has been initialized
class SeamCarverPipelineBuilder
{
public:
    SeamCarverPipelineBuilder();

    ~SeamCarverPipelineBuilder();

    /// initialize the pipeline
    void initialize();

    /// create the interface to the pipeline
    std::shared_ptr<SeamCarverPipelineInterface> createPipelineInterface();

    /// add new pipeline stage to add additional parallel processing
    /// can only be called after initialize() has been called
    bool addNewPipelineStage(PipelineStages stage);

    /// remove a parallel instance
    /// returns false if only once parallel instance since it's necessary for the pipeline operation
    bool removePipelineStage(PipelineStages stage);

    /// start the pipeline
    void runPipelineStages();

    /// stop the pipeline
    void stopPipelineStages();

    /// is this manager initialized
    bool isInitialized() const;

    /// have the pipeline stages been created
    bool arePipelineStagesCreated() const;

    /// have the pipeline queues been created
    bool arePipelineQueuesCreated() const;

    /// are the pipeline stages initialized
    bool arePipelineStagesInitialized() const;

    /// are the pipeline stages running
    bool arePipelineStagesRunning() const;

    /// get total number of pipeline stages
    size_t getTotalNumberOfPipelineStages() const;

    /// get number of pipeline stages (not counting the extra parallel ones)
    size_t getNumberOfPipelineStages() const;

    /// get total number of PARALLEL instances running in parallel for some specific stage
    size_t getNumberOfParallelStages(PipelineStages stage) const;

    // deleted to prevent misuse
    SeamCarverPipelineBuilder(const SeamCarverPipelineBuilder&) = delete;
    SeamCarverPipelineBuilder(const SeamCarverPipelineBuilder&&) = delete;
    SeamCarverPipelineBuilder& operator=(const SeamCarverPipelineBuilder&) = delete;
    SeamCarverPipelineBuilder& operator=(const SeamCarverPipelineBuilder&&) = delete;

private:
    /// have the pipeline stages been created
    bool bPipelineStagesCreated_;

    /// have the pipeline queues been created
    bool bPipelineQueuesCreated_;

    /// have the pipeline stages been started
    bool bPipelineStagesInitialized_;

    /// is the pipeline manager initialized
    bool bIsInitialized_;

    /// are the pipeline stages running
    bool bPipelineStagesRunning_;

    /// total number of pipeline stages
    size_t totalNumberOfPipelineStages_;

    /// create pipeline stages
    void createPipelineStages();

    /// create queues
    void createPipelineQueues();

    /// pass the queues and locks to the stages and start each stage's execution
    void initializePipelineStages();

    std::shared_ptr<SeamCarverQueueManager> pQueueManager_;

    std::vector<std::shared_ptr<SharedContainer<VerticalSeamCarverData*>>> queues_;

    std::vector<std::vector<std::shared_ptr<SeamCarverStage>>> pipelineStages_;

    PipelineConfigurationType pipelineConfigurationType_;

    std::shared_ptr<SeamCarverSendRcvMgr> pSenderRcvr_;
};
}  // namespace sc

#endif
