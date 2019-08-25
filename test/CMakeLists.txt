add_executable(
    PqAdapterTest
    ${CMAKE_CURRENT_SOURCE_DIR}/PqAdapterTest.cpp
)

target_link_libraries(
    PqAdapterTest
    PRIVATE
    gtest_main
)

target_include_directories(
    PqAdapterTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Common
)



add_executable(
    PriorityQueueTest
    ${CMAKE_CURRENT_SOURCE_DIR}/PriorityQueueTest.cpp
)

target_link_libraries(
    PriorityQueueTest
    PRIVATE
    gtest_main
)

target_include_directories(
    PriorityQueueTest
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
    SeamCarver
    ${OpenCV_LIBS}
    "-Xlinker --end-group"
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




add_executable(
    SeamCarverProcessorFactoryTest
    ${CMAKE_CURRENT_SOURCE_DIR}/SeamCarverProcessorFactoryTest.cpp
)

target_link_libraries(
    SeamCarverProcessorFactoryTest
    PRIVATE
    "-Xlinker --start-group"
    gtest_main
    PipelineCommon
    SeamCarver
    ${OpenCV_LIBS}
    "-Xlinker --end-group"
)




add_executable(
    SeamCarverStageFactoryTest
    ${CMAKE_CURRENT_SOURCE_DIR}/SeamCarverStageFactoryTest.cpp
)

target_link_libraries(
    SeamCarverStageFactoryTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    SeamCarver
    ${OpenCV_LIBS}
    "-Xlinker --end-group"
)

add_executable(
    VerticalSeamCarverPipelineBuilderTest
    ${CMAKE_CURRENT_SOURCE_DIR}/VerticalSeamCarverPipelineBuilderTest.cpp
)

target_link_libraries(
    VerticalSeamCarverPipelineBuilderTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    SeamCarver
    ${OpenCV_LIBS}
    "-Xlinker --end-group"
)




add_executable(
    ThreadRunnerTest
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadRunnerTest.cpp
)

target_link_libraries(
    ThreadRunnerTest
    PRIVATE
    gtest_main
)

target_include_directories(
    ThreadRunnerTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Common
)
