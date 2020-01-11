file(GLOB TestFiles_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(AllUnitTests_SRC ${AllUnitTests_SRC} ${TestFiles_SRC} PARENT_SCOPE)

foreach(TestFile ${TestFiles_SRC})
    get_filename_component(TestName ${TestFile} NAME_WE)

    add_executable(${TestName} ${TestFile})

    target_include_directories(
    ${TestName}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/Common
    )

    target_link_libraries(
    ${TestName}
    PRIVATE
        "-Wl,--start-group"
        gtest
        gtest_main
        pthread
        "-Wl,--end-group"
    )

    target_link_directories(
        ${TestName}
        PRIVATE
            /usr/local/lib
    )
endforeach()