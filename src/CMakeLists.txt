SET(
    Subdirs
    Common
    PipelineCommon
)

foreach(Subdir ${Subdirs})
    add_subdirectory(${Subdir})
endforeach()

if(BUILD_UNIT_TESTS)
    # AllUnitTests_SRC will be set in the _test subdirectories
    add_executable(AllUnitTests ${AllUnitTests_SRC})

    target_link_libraries(
        AllUnitTests
        PRIVATE
        "-Xlinker --start-group"
        gtest_main
        PipelineCommon
        "-Xlinker --end-group"
    )
endif()
