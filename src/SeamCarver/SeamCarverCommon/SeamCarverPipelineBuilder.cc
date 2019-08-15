#include "SeamCarverPipelineBuilder.hpp"

#include <cstdint>

#include "pipelineconfigurationtype.hpp"
#include "pipelinequeuetypes.hpp"
#include "seamcarverpipelineinterface.hpp"
#include "seamcarverqueuemanager.hpp"
#include "seamcarverstage.hpp"
#include "seamcarverstagefactory.hpp"
#include "VerticalSeamCarverData.hpp"

using cv::makePtr;
using cv::Ptr;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using namespace sc;

SeamCarverPipelineManager::SeamCarverPipelineManager(PipelineConfigurationType configurationType)
    : bPipelineStagesCreated_(false),
      bPipelineQueuesCreated_(false),
      bPipelineStagesInitialized_(false),
      bIsInitialized_(false),
      bPipelineStagesRunning_(false),
      totalNumberOfPipelineStages_(0),
      pipelineConfigurationType_(configurationType)
{
    pQueueManager_ = make_shared<SeamCarverQueueManager>();
}

SeamCarverPipelineManager::~SeamCarverPipelineManager() {}

void SeamCarverPipelineManager::initialize()
{
    if (!bIsInitialized_)
    {
        createPipelineStages();
        createPipelineQueues();
        initializePipelineStages();
        bIsInitialized_ = true;
    }
}

shared_ptr<SeamCarverPipelineInterface> SeamCarverPipelineManager::createPipelineInterface()
{

    return make_shared<SeamCarverPipelineInterface>(pSenderRcvr_);
}

bool SeamCarverPipelineManager::addNewPipelineStage(PipelineStages stage)
{
    // can only add a new pipeline stage when this mgr has been initialized
    if (bIsInitialized_)
    {
        shared_ptr<SeamCarverStage> p_stage = SeamCarverStageFactory::instance().createStage(
            PipelineConfigurationType::VERTICAL_DEFAULT | stage);
        // make sure the pointer returned is not null
        if (p_stage != nullptr)
        {
            ++totalNumberOfPipelineStages_;

            // initialize the stage with the SeamCarverSendRcvMgr
            p_stage->initialize(pSenderRcvr_);

            // run the stage if the rest of the stages are already running
            if (bPipelineStagesRunning_)
            {
                p_stage->runStage();
            }

            // add the stage to the vector
            pipelineStages_[stage].push_back(p_stage);

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool SeamCarverPipelineManager::removePipelineStage(PipelineStages stage)
{
    // check stage is valid
    if ((size_t)stage >= pipelineStages_.size())
    {
        return false;
    }

    // check minimum number of parallel stages
    if (pipelineStages_[(size_t)stage].size() <= 1)
    {
        return false;
    }

    // get an iterator the last stage
    vector<shared_ptr<SeamCarverStage>>::iterator iter = pipelineStages_[(size_t)stage].end();
    --iter;

    // attempt to stop the stage
    (*iter)->stopStage();

    // wait for stage to stop
    while ((*iter)->isRunning())
        ;

    // stage is stopped now, so remove the stage
    pipelineStages_[stage].erase(iter);

    return true;
}

void SeamCarverPipelineManager::runPipelineStages()
{
    if (!bPipelineStagesRunning_)
    {
        for (int32_t stage = PipelineStages::STAGE_0; stage < PipelineStages::NUM_COMPUTE_STAGES;
             ++stage)
        {
            // start the parallel stages for each 'stage'
            for (size_t p = 0; p < pipelineStages_[stage].size(); ++p)
            {
                if (pipelineStages_[stage][p] != nullptr)
                {
                    pipelineStages_[stage][p]->runStage();

                    // wait for stage to start
                    while (!(pipelineStages_[stage][p]->isRunning()))
                        ;
                }
            }
        }

        bPipelineStagesRunning_ = true;
    }
}

void SeamCarverPipelineManager::stopPipelineStages()
{
    if (bPipelineStagesRunning_)
    {
        for (size_t stage = PipelineStages::STAGE_0; stage < PipelineStages::NUM_COMPUTE_STAGES;
             ++stage)
        {
            for (size_t p = 0; p < pipelineStages_[stage].size(); ++p)
            {
                pipelineStages_[stage][p]->stopStage();

                // wait for stage to stop
                while (pipelineStages_[stage][p]->isRunning())
                    ;
            }
        }
        bPipelineStagesRunning_ = false;
    }
}

bool SeamCarverPipelineManager::isInitialized() const { return bIsInitialized_; }

bool SeamCarverPipelineManager::arePipelineStagesCreated() const { return bPipelineStagesCreated_; }

bool SeamCarverPipelineManager::arePipelineQueuesCreated() const { return bPipelineQueuesCreated_; }

bool SeamCarverPipelineManager::arePipelineStagesInitialized() const
{
    return bPipelineStagesInitialized_;
}

bool SeamCarverPipelineManager::arePipelineStagesRunning() const { return bPipelineStagesRunning_; }

size_t SeamCarverPipelineManager::getTotalNumberOfPipelineStages() const
{
    return totalNumberOfPipelineStages_;
}

size_t SeamCarverPipelineManager::getNumberOfPipelineStages() const
{
    return pipelineStages_.size();
}

size_t SeamCarverPipelineManager::getNumberOfParallelStages(PipelineStages stage) const
{
    return pipelineStages_[stage].size();
}

void SeamCarverPipelineManager::createPipelineStages()
{
    if (!bPipelineStagesCreated_)
    {
        pipelineStages_.resize(PipelineStages::NUM_COMPUTE_STAGES);

        SeamCarverStageFactory& factory = SeamCarverStageFactory::instance();

        switch (pipelineConfigurationType_)
        {
            case PipelineConfigurationType::VERTICAL_DEFAULT:
                for (int32_t stage = PipelineStages::STAGE_0;
                     stage < PipelineStages::NUM_COMPUTE_STAGES; ++stage)
                {
                    shared_ptr<SeamCarverStage> p_stage =
                        factory.createStage(PipelineConfigurationType::VERTICAL_DEFAULT | stage);
                    if (p_stage != nullptr)
                    {
                        ++totalNumberOfPipelineStages_;
                        pipelineStages_[stage].push_back(p_stage);
                    }
                }
                break;
            default:
                break;
        }

        bPipelineStagesCreated_ = true;
    }
}

void SeamCarverPipelineManager::createPipelineQueues()
{
    if (!bPipelineQueuesCreated_)
    {
        vector<int32_t> queue_ids;
        vector<PipelineQueueTypes> queue_types;
        for (int32_t stage = PipelineStages::STAGE_0; stage < PipelineStages::NUM_QUEUE_STAGES;
             ++stage)
        {
            queue_ids.push_back(stage);

            if (stage == PipelineStages::LAST_QUEUE_STAGE)
            {
                queue_types.push_back(PipelineQueueTypes::QUEUETYPE_MIN_PQ);
            }
            else
            {
                queue_types.push_back(PipelineQueueTypes::QUEUETYPE_FIFO);
            }
        }

        pQueueManager_->initialize(queue_ids, queue_types);

        pSenderRcvr_ = make_shared<SeamCarverSendRcvMgr>(pQueueManager_);

        bPipelineQueuesCreated_ = true;
    }
}

void SeamCarverPipelineManager::initializePipelineStages()
{
    if (!bPipelineStagesInitialized_ && bPipelineStagesCreated_ && bPipelineQueuesCreated_)
    {
        for (int32_t stage = PipelineStages::STAGE_0; stage < PipelineStages::NUM_COMPUTE_STAGES;
             ++stage)
        {
            // initialize the parallel stages for each 'stage'
            for (size_t p = 0; p < pipelineStages_[stage].size(); ++p)
            {
                if (pipelineStages_[stage][p] != nullptr)
                {
                    pipelineStages_[stage][p]->initialize(pSenderRcvr_);
                }
            }
        }
        bPipelineStagesInitialized_ = true;
    }
}
