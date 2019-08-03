file(GLOB SeamCarverCommon_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(
    SeamCarverCommon
    STATIC
    ${SeamCarverCommon_SRC}
)

target_include_directories(
    SeamCarverCommon
    PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
)
