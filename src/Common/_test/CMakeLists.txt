file(GLOB TestFiles_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

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
        "-Xlinker --start-group"
        gtest_main
        "-Xlinker --end-group"
    )
endforeach()