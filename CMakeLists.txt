cmake_minimum_required(VERSION 3.5)
project(p3)

# compiler
set(CMAKE_CXX_COMPILER /usr/lib/llvm-18/bin/clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -Wpedantic -Wall -Wextra -Wvla -Wno-unused-result -Wconversion")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# IPA
file(GLOB SOURCE_IPA CONFIGURE_DEPENDS src/ipa/*.cpp)

if(HEADLESS)
	add_definitions(-DHEADLESS)
endif()

# opengl
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

add_executable(ipa ${SOURCE_IPA})
target_link_libraries(ipa ${GLUT_LIBRARIES} ${OPENGL_LIBRARY})

add_executable(ipa-asan ${SOURCE_IPA})
target_compile_options(ipa-asan PRIVATE -DDEBUG -g -fsanitize=address,leak,undefined,integer,bounds,float-divide-by-zero,float-cast-overflow -fno-omit-frame-pointer -fno-sanitize-recover=all)
target_link_libraries(ipa-asan ${GLUT_LIBRARIES} ${OPENGL_LIBRARY})
target_link_options(ipa-asan PRIVATE -fsanitize=address)

add_executable(ipa-ubsan ${SOURCE_IPA})
target_compile_options(ipa-ubsan PRIVATE -DDEBUG -g -fsanitize=undefined,integer,bounds,float-divide-by-zero,implicit-conversion,float-cast-overflow,nullability -fno-omit-frame-pointer -fno-sanitize-recover=all)
target_link_libraries(ipa-ubsan ${GLUT_LIBRARIES} ${OPENGL_LIBRARY})
target_link_options(ipa-ubsan PRIVATE -fsanitize=undefined)

# PMS
file(GLOB SOURCE_PMS CONFIGURE_DEPENDS src/pms/*.cpp)

add_executable(pms ${SOURCE_PMS})

add_executable(pms-asan ${SOURCE_PMS})
target_compile_options(pms-asan PRIVATE -DDEBUG -g -fsanitize=address,leak,undefined,integer,bounds,float-divide-by-zero,float-cast-overflow -fno-omit-frame-pointer -fno-sanitize-recover=all)
target_link_options(pms-asan PRIVATE -fsanitize=address)

add_executable(pms-ubsan ${SOURCE_PMS})
target_compile_options(pms-ubsan PRIVATE -DDEBUG -g -fsanitize=undefined,integer,bounds,float-divide-by-zero,implicit-conversion,float-cast-overflow,nullability -fno-omit-frame-pointer -fno-sanitize-recover=all)
target_link_options(pms-ubsan PRIVATE -fsanitize=undefined)

