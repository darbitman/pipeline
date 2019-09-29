if(BUILD_UNIT_TESTS)
    add_subdirectory(_test)
    set(AllUnitTests_SRC ${AllUnitTests_SRC} PARENT_SCOPE)
endif(BUILD_UNIT_TESTS)
