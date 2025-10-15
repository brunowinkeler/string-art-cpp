# Add SDL3 as subdirectories
add_subdirectory(SDL EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL/include
)

# Add SDL3_image as subdirectories
set(SDLIMAGE_VENDORED ON)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL_image/include
)

# Add SDL3_ttf as subdirectories
set(SDLTTF_VENDORED ON)
add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)
# Include directories
include_directories(
    SDL_ttf/include
)
