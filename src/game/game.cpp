// Include standard libraries
#include <algorithm>

// Include project files
#include "game.h"

// Specify namespaces
using namespace std;

Game::Game(const PieceColor &active_player) :
    board(Board()),
    activePlayer(active_player)
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

    // Set active player and calculate possible moves
    this->activePlayer = WHITE;
    this->updateAllMoves();
}

Board *Game::getBoard()
{
    return &this->board;
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

void Game::updateAllMoves()
{
    this->moves.clear();

    // TODO: implement check, etc.
    for(Tile* t : this->board.getTiles()) {
        if(t->isOccupied() && this->getActivePlayer() == t->getPiece()->getColor()) {
            this->moves[t->getPosition()] = t->getPiece()->calculateMoves(this->getBoard());
        }
    }
}

enum MoveType Game::move(const unsigned int &from, const unsigned int &to)
{
    if(find(this->getPositionsPossibleMoves(from).begin(), this->getPositionsPossibleMoves(from).end(), to)
            != this->getPositionsPossibleMoves(from).end()) {
        // Move possible! TODO work with moves, for status (castling etc.)
        Piece* p = this->getBoard()->getTile(from)->getPiece();
        this->getBoard()->getTile(from)->clearPiece();
        this->getBoard()->getTile(to)->setPiece(p);

        // Update game
        this->activePlayer = this->activePlayer==WHITE ? BLACK : WHITE;
        //this->updateAllMoves();
        return MT_NORMAL;
    }

    return MT_NONE;
}

std::vector<Move> Game::getMoves(const unsigned int &position) const
{
    if(this->moves.find(position) != this->moves.end()) {
        return this->moves.at(position);
    }
    return vector<Move>();
}

std::vector<unsigned int> Game::getPositionsPossibleMoves(const unsigned int &position) const
{
    vector<Move> moves = this->getMoves(position);

    vector<unsigned int> movePositions;
    for(auto &m : moves) {
        movePositions.push_back(m.get());
    }

    return movePositions;
}


