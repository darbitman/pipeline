file(GLOB SeamCarverCommon_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

set(SeamCarver_SRC ${SeamCarver_SRC} ${SeamCarverCommon_SRC} PARENT_SCOPE)
