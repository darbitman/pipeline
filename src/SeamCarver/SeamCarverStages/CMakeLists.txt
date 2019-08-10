file(GLOB SeamCarverStages_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(SeamCarver_SRC ${SeamCarver_SRC} ${SeamCarverStages_SRC} PARENT_SCOPE)

add_subdirectory(SeamCarverDataProcessors)
