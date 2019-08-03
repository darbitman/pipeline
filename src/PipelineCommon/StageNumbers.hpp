#ifndef STAGENUMBERS_HPP
#define STAGENUMBERS_HPP

namespace sc
{
class PipelineStage
{
  public:
    const int32_t STAGE_0 = 0;
    const int32_t STAGE_1 = 1;
    const int32_t STAGE_2 = 2;
    const int32_t STAGE_3 = 3;
    const int32_t STAGE_4 = 4;
    const int32_t NUM_COMPUTE_STAGES = 5;
    const int32_t INTERFACE_STAGE = 6;
};

class QueueStage
{
  public:
    const int32_t STAGE_0 = 0;
    const int32_t STAGE_1 = 1;
    const int32_t STAGE_2 = 2;
    const int32_t STAGE_3 = 3;
    const int32_t STAGE_4 = 4;
    const int32_t STAGE_5 = 5;
    const int32_t NUM_QUEUE_STAGES = 6;
};
}  // namespace sc

#endif
