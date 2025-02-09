cmake_minimum_required (VERSION 3.5)
project ("Core")

file(GLOB_RECURSE SRC_NESTED
       #${PROJECT_SOURCE_DIR}/*.h
       ${PROJECT_SOURCE_DIR}/*.cpp )
set(ALL_SRC_FILES ${SRC_NESTED})

add_library (${PROJECT_NAME} STATIC ${ALL_SRC_FILES})

#message("HERE ${PROJECT_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw Vulkan::Vulkan glm::glm common stb)



