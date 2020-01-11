file(GLOB PipelineCommon_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_subdirectory(PipelineMessages)
add_subdirectory(PipelineMessageRouter)

add_library(
    PipelineCommon
    STATIC
    ${PipelineCommon_SRC}
)

target_include_directories(
    PipelineCommon
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/PipelineMessageRouter
    ${CMAKE_CURRENT_SOURCE_DIR}/PipelineMessages
    ${PROJECT_SOURCE_DIR}/src/Common
)

add_subdirectory(test)
