# Create library
add_library(${PROJECT_NAME}_game
    game.cpp
    utils.cpp
    operators.cpp
    player.cpp

    # Board
    board/tile.cpp
    board/move.cpp
    board/board.cpp

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

# Add board
add_subdirectory(board)
include_directories(board)
