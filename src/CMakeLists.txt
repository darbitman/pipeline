SET(
    Subdirs
    Common
    PipelineCommon
    #SeamCarver
)

foreach(Subdir ${Subdirs})
    add_subdirectory(${Subdir})
endforeach()
