# This cmake doing FetchContent to all heavy 3rd_parties
include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE) # Turn this on for GIT_PROGRESS in FetchContent_Declare

set(DEPS
    vma
    glfw
    assimp
    glm

    # Fill next
)
set(DEP_VERSTIONS # Actual tag for FetchContent_Declare
    "3.1.0"
    "3.4"
    "5.4.1"
    "1.0.1"

    # Fill next
)
set(DEP_TAGS
    "v3.1.0"
    "3.4"
    "v5.4.1"
    "1.0.1"

    # Fill next
)
set(DEP_GITS
    https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git   # VMA
    https://github.com/glfw/glfw.git                                        # glfw
    https://github.com/assimp/assimp.git                                    # assimp
    https://github.com/g-truc/glm.git                                       # glm

    # Fill next
)

foreach(DEP IN ZIP_LISTS DEPS DEP_GITS DEP_VERSTIONS DEP_TAGS)
   message(STATUS "Start work with: ${DEP_0}")
   if(NOT DEFINED ${DEP_0}_VERSION)
      set(${DEP_0}_VERSION ${DEP_2})
   endif(NOT DEFINED ${DEP_0}_VERSION)
   message(STATUS "${DEP_0} version is: ${${DEP_0}_VERSION}")

   find_package(${DEP_0} ${${DEP_0}_VERSION})
   if(${DEP_0}_FOUND)
      message(STATUS "Found ${DEP_0}!")
   else()
      message(STATUS "${DEP_0} ${${DEP_0}_VERSION} not found! Try to build it from sources")
      message(STATUS "Fetch content of ${DEP_0}: weblink: ${DEP_1}; tag: ${DEP_3}")
   FetchContent_Declare(
            ${DEP_0}
            GIT_REPOSITORY  ${DEP_1}
            GIT_TAG         ${DEP_3}
            GIT_PROGRESS   FALSE
            #USES_TERMINAL_DOWNLOAD TRUE   # <---- this is needed only for Ninja
   )

   FetchContent_GetProperties(${DEP_0})
   if(NOT ${DEP_0}_POPULATED)
            FetchContent_Populate(${DEP_0})
   endif()

   message(STATUS "Build ${DEP_0} ${${DEP_0}_VERSION} from ${${DEP_0}_SOURCE_DIR}")
   add_subdirectory(${${DEP_0}_SOURCE_DIR} ${${DEP_0}_BINARY_DIR} EXCLUDE_FROM_ALL)
   endif(${DEP_0}_FOUND)
endforeach()

