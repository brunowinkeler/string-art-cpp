file(GLOB_RECURSE STRINGART_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create executable
add_executable(${PROJ_NAME} ${STRINGART_SOURCES})

target_compile_options(${PROJ_NAME}
  PRIVATE
    -Wall -Wextra -Wpedantic
)

# Link libraries
target_link_libraries(${PROJ_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)