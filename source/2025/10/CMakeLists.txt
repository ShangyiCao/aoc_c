find_library(GLPK_LIB glpk REQUIRED)
find_path(GLPK_INCLUDE_DIR glpk.h REQUIRED)

add_executable(2025_10.exe main.c)
target_include_directories(
    2025_10.exe
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${GLPK_INCLUDE_DIR}
)
target_link_libraries(
    2025_10.exe
    ${GLPK_LIB}
)

set_target_properties(2025_10.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})




