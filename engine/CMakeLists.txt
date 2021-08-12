project(engine)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include/engine)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/deps)

# https://stackoverflow.com/a/40947954
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)

#=====================================================
#---- Dependencies -----------------------------------
#=====================================================

# ---- glfw ---------------------------
option(GLFW_BUILD_DOCS     OFF)
option(GLFW_BUILD_TESTS    OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_INSTALL        OFF)

add_subdirectory(${LIB_DIR}/glfw)

# ---- glad ---------------------------
add_subdirectory(${LIB_DIR}/glad)

# ---- stb ----------------------------
add_subdirectory(${LIB_DIR}/stb)

# ---- nuklear ------------------------
add_subdirectory(${LIB_DIR}/nuklear)

# ---- OpenGL -------------------------
find_package(OpenGL REQUIRED)


#=====================================================
#---- Project ----------------------------------------
#=====================================================

set(HEADERS
    ${INC_DIR}/core/all.h
    ${INC_DIR}/core/base.h
    ${INC_DIR}/core/cstring.h
    ${INC_DIR}/core/input.h
    ${INC_DIR}/core/list.h
    ${INC_DIR}/core/log.h
    ${INC_DIR}/core/memory.h
    ${INC_DIR}/core/stack.h
    ${INC_DIR}/core/timer.h
    ${INC_DIR}/core/vector.h

    ${INC_DIR}/graphics/all.h
    ${INC_DIR}/graphics/layer.h
    ${INC_DIR}/graphics/renderer.h
    ${INC_DIR}/graphics/window.h

    ${INC_DIR}/math/all.h
    ${INC_DIR}/math/mat.h
    ${INC_DIR}/math/types.h
    ${INC_DIR}/math/vec.h
)

set(SOURCES
    ${SRC_DIR}/core/cstring.c
    ${SRC_DIR}/core/input.c
    ${SRC_DIR}/core/list.c
    ${SRC_DIR}/core/log.c
    ${SRC_DIR}/core/memory.c
    ${SRC_DIR}/core/timer.c
    ${SRC_DIR}/core/vector.c

    ${SRC_DIR}/graphics/layer.c
    ${SRC_DIR}/graphics/renderer.c
    ${SRC_DIR}/graphics/window.c

    ${SRC_DIR}/math/mat.c
    ${SRC_DIR}/math/vec.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC nuklear glfw glad stb ${OPENGL_gl_LIBRARY})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include nuklear
    PUBLIC glfw glad stb ${OPENGL_INCLUDE_DIR})

target_compile_options(${PROJECT_NAME}
    PUBLIC -std=c99 -Wall -Wextra -Wpedantic -Werror)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC -DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})
