#ifndef STAGENUMBERS_HPP
#define STAGENUMBERS_HPP

namespace sc
{
class PipelineStage
{
  public:
    static const int32_t STAGE_0 = 0;
    static const int32_t STAGE_1 = 1;
    static const int32_t STAGE_2 = 2;
    static const int32_t STAGE_3 = 3;
    static const int32_t STAGE_4 = 4;
    static const int32_t NUM_COMPUTE_STAGES = 5;
    static const int32_t INTERFACE_STAGE = 6;
    static const int32_t MESSAGE_ROUTER = 7;
};

class QueueStage
{
  public:
    static const int32_t STAGE_0 = 0;
    static const int32_t STAGE_1 = 1;
    static const int32_t STAGE_2 = 2;
    static const int32_t STAGE_3 = 3;
    static const int32_t STAGE_4 = 4;
    static const int32_t STAGE_5 = 5;
    static const int32_t NUM_QUEUE_STAGES = 6;
};
}  // namespace sc

#endif
