# Create library
add_library(${PROJECT_NAME}_game
    game.cpp
    move.cpp
    field.cpp

    # Pieces
    piece/piece.cpp
    piece/king.cpp
    piece/linepiece.cpp
    piece/queen.cpp
    piece/rook.cpp
    piece/bishop.cpp
    piece/knight.cpp
    piece/pawn.cpp
)

# Add pieces
add_subdirectory(piece)
include_directories(piece)

# Add tests
add_subdirectory(tests)
include_directories(tests)
