file(GLOB SeamCarverStages_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_library(
    SeamCarverStages
    STATIC
    ${SeamCarverStages_SRC}
)

target_include_directories(
    SeamCarverStages
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages
    ${PROJECT_SOURCE_DIR}/src/SeamCarverCommon
    ${PROJECT_SOURCE_DIR}/src/Stages
    ${OpenCV_INCLUDE_DIRS}
)
