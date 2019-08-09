#[[
file(GLOB Test_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(
    unit_tests
    ${Test_SRC}
)

target_link_libraries(
    unit_tests
    PRIVATE
    gtest_main
    SeamCarverStages
    PipelineManagement
    SeamCarverCommon
    ${OpenCV_LIBS}
)

target_include_directories(
    unit_tests
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/common
    ${PROJECT_SOURCE_DIR}/include/pipelinemanagement
    ${PROJECT_SOURCE_DIR}/include/stages
    ${OpenCV_INCLUDE_DIRS}
)

target_compile_definitions(
    unit_tests
    PRIVATE
        -DIMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/eagle.jpg"
)



add_executable(
    SeamCarverPipelineInterfaceTest
    test_seamcarverpipelineinterface.cpp
)

target_link_libraries(
    SeamCarverPipelineInterfaceTest
    PRIVATE
    gtest_main
    SeamCarverStages
    PipelineManagement
    SeamCarverCommon
    ${OpenCV_LIBS}
)

target_compile_definitions(
    SeamCarverPipelineInterfaceTest
    PRIVATE
        -DIMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/eagle.jpg"
)



add_executable(
    CumulativePathEnergyCalculatorStageTest
    test_cumulativepathenergycalculatorstage.cpp
)

target_link_libraries(
    CumulativePathEnergyCalculatorStageTest
    PRIVATE
    gtest_main
    SeamCarverStages
    PipelineManagement
    SeamCarverCommon
    ${OpenCV_LIBS}
)

target_compile_definitions(
    CumulativePathEnergyCalculatorStageTest
    PRIVATE
        -DIMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/eagle.jpg"
)
]]

add_executable(
    ConstSizePriorityQueueTest
    ${CMAKE_CURRENT_SOURCE_DIR}/ConstSizePriorityQueueTest.cpp
)

target_link_libraries(
    ConstSizePriorityQueueTest
    PRIVATE
    gtest_main
)

target_include_directories(
    ConstSizePriorityQueueTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Common
)



add_executable(
    PipelineQueueManagerTest
    ${CMAKE_CURRENT_SOURCE_DIR}/PipelineQueueManagerTest.cpp
)

target_link_libraries(
    PipelineQueueManagerTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    SeamCarverCommon
    ${OpenCV_LIBS}
    "-Xlinker --end-group"
)

target_include_directories(
    PipelineQueueManagerTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages
    ${PROJECT_SOURCE_DIR}/src/SeamCarverCommon
    ${OpenCV_INCLUDE_DIRS}
)



add_executable(
    PipelineSenderReceiverTest
    ${CMAKE_CURRENT_SOURCE_DIR}/PipelineSenderReceiverTest.cpp
)

target_link_libraries(
    PipelineSenderReceiverTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    "-Xlinker --end-group"
)

target_include_directories(
    PipelineSenderReceiverTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages    
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/SeamCarverCommon
)



add_executable(
    ComputeEnergyStageTest
    ${CMAKE_CURRENT_SOURCE_DIR}/ComputeEnergyStageTest.cpp
)

target_link_libraries(
    ComputeEnergyStageTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    SeamCarverCommon
    SeamCarverStages
    "-Xlinker --end-group"
)

target_include_directories(
    ComputeEnergyStageTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon/PipelineMessages    
    ${PROJECT_SOURCE_DIR}/src/Common
    ${PROJECT_SOURCE_DIR}/src/PipelineCommon
    ${PROJECT_SOURCE_DIR}/src/SeamCarverCommon
)
