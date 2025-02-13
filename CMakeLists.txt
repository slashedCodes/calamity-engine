cmake_minimum_required(VERSION 3.5)

project(sdl2-image)

add_executable(${PROJECT_NAME} engine.cpp main.cpp)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(PSP)
    # Create an EBOOT.PBP file
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()
