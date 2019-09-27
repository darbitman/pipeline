#pragma once

namespace sc
{
class ComponentId
{
  public:
    static constexpr uint32_t UNKNOWN_COMPONENT{0};
    static constexpr uint32_t MESSAGE_ROUTER{1};
    static constexpr uint32_t INTERFACE_STAGE{2};
    static constexpr uint32_t STAGE_0{3};
    static constexpr uint32_t STAGE_1{4};
    static constexpr uint32_t STAGE_2{5};
    static constexpr uint32_t STAGE_3{6};
    static constexpr uint32_t STAGE_4{7};
};

class ComponentLinkType
{
  public:
    static constexpr uint32_t QUEUE_TYPE_UNKNOWN{0};
    static constexpr uint32_t QUEUE_TYPE_FIFO{1};
    static constexpr uint32_t QUEUE_TYPE_MIN_PQ{2};
};

class MessageType
{
  public:
    static constexpr uint32_t MESSAGE_TYPE_UNKNOWN{0};
    static constexpr uint32_t MESSAGE_TYPE_PIPELINE_DATA{1};
    static constexpr uint32_t MESSAGE_TYPE_SHUTDOWN{2};
    static constexpr uint32_t MESSAGE_TYPE_REGISTER_WITH_ROUTER{3};
    static constexpr uint32_t MESSAGE_TYPE_UNREGISTER_WITH_ROUTER{4};
};

}  // namespace sc
