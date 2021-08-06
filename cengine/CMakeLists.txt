project(engine)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include/cengine)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

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

# ---- OpenGL -------------------------
find_package(OpenGL REQUIRED)


#=====================================================
#---- Project ----------------------------------------
#=====================================================

set(SOURCES
    ${SRC_DIR}/core/input.c
    ${SRC_DIR}/core/log.c
    ${SRC_DIR}/core/memory.c
    ${SRC_DIR}/core/timer.c

    ${SRC_DIR}/data/vector.c
    ${SRC_DIR}/data/dstring.c
    ${SRC_DIR}/data/list.c

    ${SRC_DIR}/graphics/window.c
)

set(HEADERS
    ${INC_DIR}/core/base.h
    ${INC_DIR}/core/input.h
    ${INC_DIR}/core/log.h
    ${INC_DIR}/core/memory.h
    ${INC_DIR}/core/timer.h

    ${INC_DIR}/data/vector.c
    ${INC_DIR}/data/dstring.c
    ${INC_DIR}/data/list.c

    ${INC_DIR}/graphics/window.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    PRIVATE glfw glad stb ${OPENGL_gl_LIBRARY}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE glfw glad stb ${OPENGL_INCLUDE_DIR}
)

target_compile_options(${PROJECT_NAME}
    PRIVATE -std=c99 -Wall -Wextra -Wpedantic -Werror
)
