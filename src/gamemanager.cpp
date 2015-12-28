// Include standard libraries
#include <algorithm>
#include <string>
#include <iostream>

// Include project files
#include "gamemanager.h"
#include "piece/pawn.h"
#include "piece/queen.h"
#include "piece/rook.h"
#include "piece/bishop.h"
#include "piece/knight.h"

// Specify namespaces
using namespace std;

GameManager::GameManager(const int &board_layout)
{
    this->initBoard(board_layout);
}

Board *GameManager::getBoard()
{
    return &this->board;
}

void GameManager::initBoard(const int &board_layout)
{
    // Create new board
    this->board = Board();

    switch(board_layout) {
    case 1:
        this->promotionTest();
        break;
    case 2:
        this->castlingTest();
        break;
    case 3:
        this->movingInCheckTest();
        break;
    case 4:
        this->moveOutCheckTest();
        break;
    case 5:
        this->moveOutCheckTest2();
        break;
    default:
        this->standardBoard();
        break;
    }

    // Setup players
    this->whitePlayer = Player(WHITE, this->getBoard());
    this->blackPlayer = Player(BLACK, this->getBoard());

}

void GameManager::standardBoard()
{
    // Pawns
    for(unsigned int i=0; i<8; i++) {
        this->board.addPiece(i, 1, PAWN, WHITE);
        this->board.addPiece(i, 6, PAWN, BLACK);
    }

    // White pieces
    this->board.addPiece(4, 0, KING, WHITE);
    this->board.addPiece(3, 0, QUEEN, WHITE);
    this->board.addPiece(0, 0, ROOK, WHITE);
    this->board.addPiece(7, 0, ROOK, WHITE);
    this->board.addPiece(2, 0, BISHOP, WHITE);
    this->board.addPiece(5, 0, BISHOP, WHITE);
    this->board.addPiece(1, 0, KNIGHT, WHITE);
    this->board.addPiece(6, 0, KNIGHT, WHITE);

    // Black pieces
    this->board.addPiece(4, 7, KING, BLACK);
    this->board.addPiece(3, 7, QUEEN, BLACK);
    this->board.addPiece(0, 7, ROOK, BLACK);
    this->board.addPiece(7, 7, ROOK, BLACK);
    this->board.addPiece(2, 7, BISHOP, BLACK);
    this->board.addPiece(5, 7, BISHOP, BLACK);
    this->board.addPiece(1, 7, KNIGHT, BLACK);
    this->board.addPiece(6, 7, KNIGHT, BLACK);

    // Set active player
    this->board.setActiveColor(WHITE);
}

Player *GameManager::getActivePlayer()
{
    if(this->board.getActiveColor() == WHITE) {
        return &this->whitePlayer;
    } else {
        return &this->blackPlayer;
    }
}
