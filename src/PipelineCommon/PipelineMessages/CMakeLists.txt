file(GLOB PipelineMessages_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(PipelineCommon_SRC ${PipelineCommon_SRC} ${PipelineMessages_SRC} PARENT_SCOPE)
