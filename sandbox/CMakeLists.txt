project(sandbox)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

#=====================================================
#---- Dependencies -----------------------------------
#=====================================================


#=====================================================
#---- Project ----------------------------------------
#=====================================================

set(SOURCES
    ${SRC_DIR}/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC engine)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${INC_DIR} engine)

target_compile_options(${PROJECT_NAME}
    PUBLIC -Wall -Wextra -Wpedantic -Werror)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)
