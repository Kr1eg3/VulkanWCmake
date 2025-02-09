# CMakeList.txt : CMake project for KovalskiyEngine, include source and define
cmake_minimum_required (VERSION 3.5)
project ("KovalskiyEngine")
find_package(PkgConfig REQUIRED)

include(cmake/deps.cmake)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
message(STATUS "Root directory: ${ROOT_DIR}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_compile_definitions(NDEBUG=0)
add_compile_definitions(STB_IMAGE_STATIC)

#  __      __    _ _
#  \ \    / /   | | |
#   \ \  / /   _| | | ____ _ _ __
#    \ \/ / | | | | |/ / _` | '_ \
#     \  /| |_| | |   < (_| | | | |
#      \/  \__,_|_|_|\_\__,_|_| |_|
# # # # # # # # # # # # # # # # # # #
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Found Vulkan!")
endif()

#   _   ___      ___     _ _         _____  _              __   __
#  | \ | \ \    / (_)   | (_)       |  __ \| |             \ \ / /
#  |  \| |\ \  / / _  __| |_  __ _  | |__) | |__  _   _ ___ \ V /
#  | . ` | \ \/ / | |/ _` | |/ _` | |  ___/| '_ \| | | / __| > <
#  | |\  |  \  /  | | (_| | | (_| | | |    | | | | |_| \__ \/ . \
#  |_| \_|   \/   |_|\__,_|_|\__,_| |_|    |_| |_|\__, |___/_/ \_\
#                                                  __/ |
#                                                 |___/
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#find_package(physx)  # BIG TODO

add_subdirectory(common)
add_subdirectory(third_party)
add_subdirectory(engine)
add_subdirectory(app)

file(GLOB SRC_FILES
       ${PROJECT_SOURCE_DIR}/*.cpp)
#file(GLOB_RECURSE SRC_NESTED
#       ${PROJECT_SOURCE_DIR}/app/*.cpp )
set(ALL_SRC_FILES ${SRC_FILES}) #${SRC_NESTED})

message(STATUS "Here is all sources for Main" ${ALL_SRC_FILES})

add_executable (KovalskiyEngine ${ALL_SRC_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KovalskiyEngine PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
#target_include_directories(${PROJECT_NAME} PRIVATE "${ROOT_DIR}/app/include")
target_link_libraries(KovalskiyEngine PRIVATE Application)



