SET(
    Subdirs
    Common
    PipelineCommon
    SeamCarverCommon
    Stages
)

foreach(Subdir ${Subdirs})
    add_subdirectory(${Subdir})
endforeach()
