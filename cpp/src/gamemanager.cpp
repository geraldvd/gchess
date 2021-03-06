// Include standard libraries
#include <algorithm>
#include <string>

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
        this->enPassantTest();
        break;
    case 4:
        this->movingInCheckTest();
        break;
    case 5:
        this->moveOutCheckTest();
        break;
    case 6:
        this->staleMateTest();
        break;
    default:
        this->standardBoard();
        break;
    }

    this->getBoard()->updateMoves();
    this->moveHistory.clear();
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
    this->board.setActivePlayer(WHITE);
}

void GameManager::promotionTest()
{
    // Kings
    this->board.addPiece(4, 0, KING, WHITE);
    this->board.addPiece(4, 7, KING, BLACK);

    // Promotion pawn
    this->board.addPiece(2, 6, PAWN, WHITE);
    this->board.addPiece(6, 1, PAWN, BLACK);

    // Extra piece (for promotion via capturing)
    this->board.addPiece(1, 7, KNIGHT, BLACK);

    // Set active player
    this->board.setActivePlayer(WHITE);
}

void GameManager::castlingTest()
{
    // Kings
    this->board.addPiece(4, 0, KING, WHITE);
    this->board.addPiece(4, 7, KING, BLACK);

    // Rooks
    this->board.addPiece(0, 0, ROOK, WHITE);
    this->board.addPiece(7, 0, ROOK, WHITE);
    this->board.addPiece(0, 7, ROOK, BLACK);
    this->board.addPiece(7, 7, ROOK, BLACK);

    // Attack one of the fields
    this->board.addPiece(5, 2, BISHOP, BLACK);

    // Set active player
    this->board.setActivePlayer(WHITE);
}

void GameManager::moveOutCheckTest() {
    // Kings
    this->board.addPiece(4, 0, KING, WHITE);
    this->board.addPiece(7, 7, KING, BLACK);

    // Other pieces
    this->board.addPiece(0, 7, ROOK, WHITE);
    this->board.addPiece(4, 7, KNIGHT, BLACK);

    // Set active player
    this->board.setActivePlayer(BLACK);
}

void GameManager::enPassantTest()
{
    // Kings
    this->board.addPiece(4, 0, KING, WHITE);
    this->board.addPiece(4, 7, KING, BLACK);

    // Pawns
    this->board.addPiece(4, 6, PAWN, BLACK);
    this->board.addPiece(3, 4, PAWN, WHITE);
    this->board.addPiece(2, 1, PAWN, WHITE);
    this->board.addPiece(3, 3, PAWN, BLACK);

    // Set active player
    this->board.setActivePlayer(BLACK);
}

void GameManager::staleMateTest()
{
    // Kings
    this->board.addPiece(0, 0, KING, WHITE, true);
    this->board.addPiece(7, 7, KING, BLACK, true);

    // Other pieces
    this->board.addPiece(1, 2, ROOK, BLACK, true);
    this->board.addPiece(3, 2, KNIGHT, BLACK);

    // Set active player
    this->board.setActivePlayer(BLACK);
}

void GameManager::movingInCheckTest()
{
    // Kings
    this->board.addPiece(1, 0, KING, WHITE);
    this->board.addPiece(7, 5, KING, BLACK);

    // Queen
    this->board.addPiece(1, 7, QUEEN, BLACK);

    // Add blocking piece
    this->board.addPiece(1, 3, KNIGHT, WHITE);

    // Set active player
    this->board.setActivePlayer(WHITE);
}



MoveStatus GameManager::move(const Field &from, const Field &to, const PromotionType &pt)
{
    for(auto &m : this->board.getMoves()) {
        if(m.getMovingPiece()->getColor() == this->board.getActivePlayer() &&
                *m.getMovingPiece()->getTile() == from && m.getDestination() == to) {
            if(m.getMoveType() == MT_PROMOTION && m.getPromotionType() != pt) {
                // Wrong promotion type
                continue;
            }
            // Add move to history (with board before move)
            this->moveHistory.push_back(pair<Move,std::string>(m,this->board.get()));

            // Perform move
            this->board = this->board.move(m);
            this->board.updateMoves();

            return MS_OK;
        }
    }
    return MS_INVALID;
}

std::vector<std::pair<Move, string> > GameManager::getMoveHistory() const
{
    return this->moveHistory;
}

bool GameManager::revertMove(const string &b)
{
    // Check whether move existed
    bool validBoard{false};
    vector<pair<Move, string> > previousMoves;
    for(auto &m : this->moveHistory) {
        if(m.second == b) {
            validBoard = true;
            break;
        }
        previousMoves.push_back(m);
    }

    // Revert board if allowed
    if(validBoard) {
        this->moveHistory = previousMoves;
        this->board = Board(b);
        this->board.updateMoves();
    }

    return validBoard;
}
