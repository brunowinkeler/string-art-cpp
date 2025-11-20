file(GLOB_RECURSE STRINGART_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE STRINGART_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJ_NAME} ${STRINGART_SOURCES} ${STRINGART_HEADERS})

target_compile_options(${PROJ_NAME}
  PRIVATE
    -Wall -Wextra -Wpedantic
)

# Link libraries
target_link_libraries(${PROJ_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)
