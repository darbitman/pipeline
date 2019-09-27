file(GLOB PipelineMessageRouter_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(PipelineCommon_SRC ${PipelineCommon_SRC} ${PipelineMessageRouter_SRC} PARENT_SCOPE)
