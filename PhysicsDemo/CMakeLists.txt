cmake_minimum_required(VERSION 3.16)

project(PhysicsDemo LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(HEADER_FILES include/circle_wrapper.hpp include/physics_demo_runner.hpp include/body_wrapper.hpp include/button.hpp include/polygon_wrapper.hpp include/demo_menu.hpp include/vector_adapter.hpp)
include_directories(include)

set(SOURCES sources/main.cpp sources/circle_wrapper.cpp sources/physics_demo_runner.cpp "sources/body_wrapper.cpp" "sources/button.cpp" "sources/demo_menu.cpp" "sources/rectangle_wrapper.cpp"  "sources/polygon_wrapper.cpp")
add_executable(PhysicsDemo ${SOURCES})
target_compile_definitions(PhysicsDemo PRIVATE "PROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}/assets\"")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics 2DPhysicsEngine sfml-window)
if(WIN32)
    add_custom_command(
        TARGET PhysicsDemo
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PhysicsDemo>
        VERBATIM)
endif()


install(TARGETS PhysicsDemo)