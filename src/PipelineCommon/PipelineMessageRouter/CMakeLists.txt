file(GLOB PipelineMessageRouter_SRC CONFIGURE_DEPENDS "*.cpp")

set(PipelineCommon_SRC ${PipelineCommon_SRC} ${PipelineMessageRouter_SRC} PARENT_SCOPE)
