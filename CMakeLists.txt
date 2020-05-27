cmake_minimum_required(VERSION 3.0.0)
project(VulkanEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*)

add_executable(VulkanEngine ${SRC})

target_include_directories(VulkanEngine PUBLIC
    Include
    ${VK_INCLUDE_DIRS}
    ${VK_INCLUDE_DIRS}/vulkan
)



if (LINUX)
	target_compile_definitions(VulkanEngine PRIVATE -DVK_USE_PLATFORM_XLIB_KHR)

	target_include_directories(VulkanEngine PRIVATE Vulkan::Vulkan)
	target_include_directories(VulkanEngine PRIVATE ${X11+INCLUDE_DIR})
	target_link_libraries(VulkanEngine PRIVATE Vulkan::Vulkan)
	target_link_libraries(VulkanEngine PRIVATE ${X11_LIBRARIES} -lm)
endif (LINUX)
if (WIN32)
	target_compile_definitions(VulkanEngine PRIVATE -DVK_USE_PLATFORM_WIN32LIB_KHR)

	target_include_directories(VulkanEngine PRIVATE Vulkan::Vulkan)
	target_include_directories(VulkanEngine PRIVATE ${WIN32+INCLUDE_DIR})
	target_link_libraries(VulkanEngine PRIVATE Vulkan::Vulkan)
	target_link_libraries(VulkanEngine PRIVATE ${WIN32_LIBRARIES} -lm)   
endif (WIN32)

#glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(VulkanEngine PRIVATE glfw)

#glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(VulkanEngine PRIVATE glm)

file(COPY ${PROJECT_SOURCE_DIR}/EngineAssets DESTINATION ${PROJECT_BINARY_DIR})

