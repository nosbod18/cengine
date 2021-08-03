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
   ${SRC_DIR}/util/log.c
   ${SRC_DIR}/util/timer.c
)

set(HEADERS
    ${INC_DIR}/util/log.h
    ${INC_DIR}/util/timer.h
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
    PRIVATE -std=c99 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror
)
