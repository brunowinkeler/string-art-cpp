# Add SDL3 as subdirectories
set(SDL_CCACHE ON CACHE BOOL "" FORCE)
add_subdirectory(SDL EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL/include
)

# Add SDL3_image as subdirectories
set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)
# Enable only PNG, JPG, and GIF support in SDL3_image
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP ON CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDLIMAGE_PNM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SVG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XV OFF CACHE BOOL "" FORCE)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL_image/include
)

# Add SDL3_ttf as subdirectories
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL_ttf/include
)

# Add spdlog as subdirectory
add_subdirectory(spdlog)
include_directories(
    spdlog/include
)

# Add nlohmann as single file include
add_subdirectory(nlohmann_json)
include_directories(
    nlohmann_json/include
)
