cmake_minimum_required(VERSION 3.10)
project(GPR5300)


if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "shaders/*.frag"
    "shaders/*.vert"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

include_directories(include ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE PROJECT_SRC src/*.cpp include/*.h)

include_directories(externals/imgui)

#SDL
set(SDL_VERSION 2.0.9)
set(SDL_DIR ${EXTERNAL_DIR}/SDL2-${SDL_VERSION}/)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
add_subdirectory(${SDL_DIR})
include_directories(${SDL2_DIR}/include ${SDL2_DIR}/src)
LIST(APPEND PROJECT_LIBRARIES
        SDL2-static)
if(MSVC)
LIST(APPEND PROJECT_LIBRARIES
        SDL2main)
endif(MSVC)

#GLM
set(GLM_DIR ${EXTERNAL_DIR}/glm)
IF(NOT EXISTS ${GLM_DIR})
message(FATAL_ERROR "Please do git submodule update --init --recursive")
ENDIF()
include_directories(${GLM_DIR})

#stb_image
set(STB_DIR ${EXTERNAL_DIR}/stb_image/stb_image.h)
include_directories(${STB_DIR})

#VULKAN
find_package(Vulkan)
include_directories(${Vulkan_INCLUDE_DIRS})
LIST(APPEND PROJECT_LIBRARIES ${Vulkan_LIBRARY})

#Main
SET(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)
file(GLOB MAIN_FILES ${MAIN_DIR}/*.cpp )

foreach(main_file ${MAIN_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH main_relative_path ${MAIN_DIR} ${main_file})
    string( REPLACE ".cpp" "" main_name ${main_relative_path} )
    add_executable(${main_name} ${main_file} ${PROJECT_SRC})
    # Make sure YourLib is linked to each app
    target_link_libraries(${main_name} PUBLIC ${PROJECT_LIBRARIES})
    set_property(TARGET ${main_name} PROPERTY CXX_STANDARD 17)


    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi")
    elseif(UNIX)
        set_target_properties(${main_name} PROPERTIES COMPILE_FLAGS "-save-temps -ffast-math -march=native")
    ENDIF(MSVC)
    set_target_properties (${main_name} PROPERTIES
            FOLDER Courses)
    IF(APPLE)
        set_target_properties(${main_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
    ENDIF()

	
	add_dependencies(${main_name} Shaders)

endforeach()
