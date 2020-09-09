cmake_minimum_required(VERSION 3.0.0)
project(SpeedEngineVk VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(X11 REQUIRED)
find_package(Vulkan REQUIRED)


file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*)

add_executable(SpeedEngineVk ${SRC})

target_include_directories(SpeedEngineVk PUBLIC
    Include
)



if (UNIX AND NOT APPLE)
    set (LINUX TRUE)
	target_compile_definitions(SpeedEngineVk PRIVATE -DVK_USE_PLATFORM_XLIB_KHR)
	target_include_directories(SpeedEngineVk PRIVATE Vulkan::Vulkan)
	target_include_directories(SpeedEngineVk PRIVATE ${X11+INCLUDE_DIR})
	target_link_libraries(SpeedEngineVk PRIVATE Vulkan::Vulkan)
	target_link_libraries(SpeedEngineVk PRIVATE ${X11_LIBRARIES} -lm)
endif ()

if (WIN32)
	target_compile_definitions(SpeedEngineVk PRIVATE -DVK_USE_PLATFORM_WIN32LIB_KHR)
	target_include_directories(SpeedEngineVk PRIVATE Vulkan::Vulkan)
	target_include_directories(SpeedEngineVk PRIVATE ${WIN32+INCLUDE_DIR})
	target_link_libraries(SpeedEngineVk PRIVATE Vulkan::Vulkan)
	target_link_libraries(SpeedEngineVk PRIVATE ${WIN32_LIBRARIES})   
endif ()

#glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(SpeedEngineVk PRIVATE glfw)

#glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(SpeedEngineVk PRIVATE glm)

#glslang 
add_subdirectory(lib/glslang EXCLUDE_FROM_ALL)
target_link_libraries(SpeedEngineVk PRIVATE glslang SPIRV)

file(COPY ${PROJECT_SOURCE_DIR}/EngineAssets DESTINATION ${PROJECT_BINARY_DIR})

