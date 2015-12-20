#include "game.h"

Game::Game() :
    board(Board())
{

}

void Game::newGame()
{
    // Clean board
    this->board = Board();

    // Pawns
    for(int i=8; i<16; i++) {
        this->board.addPiece(i, PAWN, WHITE);
        this->board.addPiece(40+i, PAWN, BLACK);
    }

    // White pieces
    this->board.addPiece(4, KING, WHITE);
    this->board.addPiece(3, QUEEN, WHITE);
    this->board.addPiece(0, ROOK, WHITE);
    this->board.addPiece(7, ROOK, WHITE);
    this->board.addPiece(2, BISHOP, WHITE);
    this->board.addPiece(5, BISHOP, WHITE);
    this->board.addPiece(1, KNIGHT, WHITE);
    this->board.addPiece(6, KNIGHT, WHITE);

    // Black pieces
    this->board.addPiece(60, KING, BLACK);
    this->board.addPiece(59, QUEEN, BLACK);
    this->board.addPiece(56, ROOK, BLACK);
    this->board.addPiece(63, ROOK, BLACK);
    this->board.addPiece(58, BISHOP, BLACK);
    this->board.addPiece(61, BISHOP, BLACK);
    this->board.addPiece(57, KNIGHT, BLACK);
    this->board.addPiece(62, KNIGHT, BLACK);

    // Set active player
    this->activePlayer = WHITE;
}

Board Game::getBoard() const
{
    return this->board;
}

PieceColor Game::getActivePlayer() const
{
    return this->activePlayer;
}

std::string Game::getActivePlayerString() const
{
    if(this->activePlayer == WHITE)
        return "White";
    else
        return "Black";
}

