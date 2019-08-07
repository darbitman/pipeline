#ifndef PIPELINEMESSAGETYPE_HPP
#define PIPELINEMESSAGETYPE_HPP

namespace sc
{
enum EPipelineMessageType
{
    MESSAGE_TYPE_UNKNOWN = 0,
    MESSAGE_TYPE_PIPELINE_DATA = 1,
    MESSAGE_TYPE_SHUTDOWN = 2,
    MESSAGE_TYPE_REGISTER_WITH_ROUTER = 3,
    MESSAGE_TYPE_UNREGISTER_WITH_ROUTER = 4
};
}

#endif