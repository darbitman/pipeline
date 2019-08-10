
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
    ComputeEnergyStageTest
    ${CMAKE_CURRENT_SOURCE_DIR}/ComputeEnergyStageTest.cpp
)

target_link_libraries(
    ComputeEnergyStageTest
    PRIVATE
    gtest_main
    "-Xlinker --start-group"
    PipelineCommon
    "-Wl,--whole-archive"
    SeamCarver
    "-Wl,--no-whole-archive"
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
    "-Wl,--whole-archive"
    SeamCarver
    "-Wl,--no-whole-archive"
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
    "-Wl,--whole-archive"
    SeamCarver
    "-Wl,--no-whole-archive"
    "-Xlinker --end-group"
)
