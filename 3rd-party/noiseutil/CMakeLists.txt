set(LIBNOISESTATIC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/noiseutils.cpp)
add_library(libnoiseutil-static STATIC ${LIBNOISESTATIC_SOURCE})


#(${PROJECT_SOURCE_DIR}/3rd-party/libnoise/src)
target_link_libraries(libnoiseutil-static noise-static)
target_include_directories(libnoiseutil-static PRIVATE ${PROJECT_SOURCE_DIR}/3rd-party/libnoise/src)