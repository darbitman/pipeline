#ifndef PIPELINEQUEUETYPES_HPP
#define PIPELINEQUEUETYPES_HPP

#include <cstdint>

namespace sc
{
class PipelineQueueTypes
{
  public:
    static const int32_t QUEUE_TYPE_FIFO = 0;
    static const int32_t QUEUE_TYPE_MIN_PQ = 1;
};
};  // namespace sc

#endif
