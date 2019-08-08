#ifndef PIPELINECOMMON_HPP
#define PIPELINECOMMON_HPP

namespace sc
{
enum EPipelineStageId
{
    MESSAGE_ROUTER,
    INTERFACE_STAGE,
    STAGE_0,
    STAGE_1,
    STAGE_2,
    STAGE_3,
    STAGE_4
};

enum EPipelineQueueType
{
    QUEUE_TYPE_FIFO,
    QUEUE_TYPE_MIN_PQ
};

enum EPipelineMessageType
{
    MESSAGE_TYPE_UNKNOWN = 0,
    MESSAGE_TYPE_PIPELINE_DATA = 1,
    MESSAGE_TYPE_SHUTDOWN = 2,
    MESSAGE_TYPE_REGISTER_WITH_ROUTER = 3,
    MESSAGE_TYPE_UNREGISTER_WITH_ROUTER = 4
};
}  // namespace sc
#endif
