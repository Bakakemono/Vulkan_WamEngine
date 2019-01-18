cmake_minimum_required(VERSION 3.10)
project(GPR5300)


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

include_directories(include ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE PROJECT_SRC src/*.cpp include/*.h)

#SDL
set(SDL_VERSION 2.0.9)
set(SDL_DIR ${EXTERNAL_DIR}/SDL2-${SDL_VERSION}/)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
add_subdirectory(${SDL_DIR})
include_directories(${SDL2_DIR}/include)
LIST(APPEND PROJECT_LIBRARIES
        SDL2-static)
if(MSVC)
LIST(APPEND PROJECT_LIBRARIES
        SDL2main)
endif(MSVC)

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
endforeach()
