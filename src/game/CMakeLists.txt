add_library(${PROJECT_NAME}_game
    # Game classes
    game.cpp

    # Pieces
    piece.cpp
    king.cpp
    linepiece.cpp
    queen.cpp
    rook.cpp
    bishop.cpp
    knight.cpp
    pawn.cpp

    # Helpers
    field.cpp
)

add_subdirectory(tests)
include_directories(tests)
