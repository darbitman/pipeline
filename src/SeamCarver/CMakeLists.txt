file(GLOB SeamCarver_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_subdirectory(SeamCarverCommon)
add_subdirectory(SeamCarverStages)

add_library(
    SeamCarver
    STATIC
    ${SeamCarver_SRC}
)

target_include_directories(
    SeamCarver
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages
    ${PROJECT_SOURCE_DIR}/src/SeamCarver/SeamCarverCommon
    ${PROJECT_SOURCE_DIR}/src/SeamCarver/SeamCarverStages/
    ${PROJECT_SOURCE_DIR}/src/SeamCarver/SeamCarverStages/SeamCarverDataProcessors
    ${OpenCV_INCLUDE_DIRS}
)
