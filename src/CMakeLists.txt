SET(
    Subdirs
    Common
    PipelineCommon
)

foreach(Subdir ${Subdirs})
    add_subdirectory(${Subdir})
endforeach()
