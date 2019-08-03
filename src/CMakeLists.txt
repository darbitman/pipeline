SET(
    Subdirs
    Common
    PipelineCommon
    SeamCarverCommon
    #pipelinemanagement
    #stages
)

foreach(Subdir ${Subdirs})
    add_subdirectory(${Subdir})
endforeach()
