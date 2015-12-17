# Create library
add_library(${PROJECT_NAME}_game
    game.cpp
    field.cpp
)

# Add pieces
add_subdirectory(piece)
include_directories(piece)
target_link_libraries(${PROJECT_NAME}_game ${PROJECT_NAME}_game_piece)

# Add tests
add_subdirectory(tests)
include_directories(tests)
