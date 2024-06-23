cmake_minimum_required(VERSION 3.16)
project(2DPhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(HEADER_FILES include/collision_resolver.hpp include/world.hpp include/collisions.hpp include/body.hpp
include/2dMath.hpp include/shape.hpp include/rectangle_capsule.hpp include/circle.hpp
include/polygon.hpp include/collision_grid.hpp include/manifold.hpp include/rectangle.hpp include/logger.hpp include/2DPhysicsEngine.hpp)

add_library(${PROJECT_NAME} STATIC)

target_sources(2DPhysicsEngine PRIVATE
    "sources/collision_resolver.cpp"
	sources/world.cpp
	sources/body.cpp
    sources/2dMath.cpp
    sources/circle.cpp
    sources/polygon.cpp
    sources/collision_grid.cpp
    sources/rectangle.cpp
    sources/logger.cpp
	${HEADER_FILES} "sources/shape.cpp")

target_include_directories(2DPhysicsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(2DPhysicsEngine PRIVATE cxx_std_17)

add_library(PhysicsDemo::2DPhysicsEngine ALIAS 2DPhysicsEngine)

