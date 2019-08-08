file(GLOB PipelineCommon_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_subdirectory(PipelineMessages)

add_library(
    PipelineCommon
    STATIC
    ${PipelineCommon_SRC}
)

target_include_directories(
    PipelineCommon
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages
    ${PROJECT_SOURCE_DIR}/src/SeamCarverCommon
    ${OpenCV_INCLUDE_DIRS}
)
