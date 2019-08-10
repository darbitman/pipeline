file(GLOB SeamCarverStages_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_subdirectory(SeamCarverDataProcessors)

set(SeamCarver_SRC ${SeamCarver_SRC} ${SeamCarverStages_SRC} PARENT_SCOPE)
