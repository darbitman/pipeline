file(GLOB Stages_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(
    SeamCarverStages
    STATIC
    ${Stages_SRC}
)

target_include_directories(
    SeamCarverStages
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/common
    ${PROJECT_SOURCE_DIR}/include/pipelinemanagement
    ${PROJECT_SOURCE_DIR}/include/stages
    ${OpenCV_INCLUDE_DIRS}
)
