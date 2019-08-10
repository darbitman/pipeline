file(GLOB SeamCarverDataProcessors_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(SeamCarver_SRC ${SeamCarver_SRC} ${SeamCarverDataProcessors_SRC} PARENT_SCOPE)
