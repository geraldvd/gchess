// Include standard libraries
#include <algorithm>
#include <string>
#include <iostream>

// Include project files
#include "game.h"
#include "piece/pawn.h"
#include "piece/queen.h"
#include "piece/rook.h"
#include "piece/bishop.h"
#include "piece/knight.h"

// Specify namespaces
using namespace std;

Game::Game(const PieceColor &active_player) :
    board(Board()),
    activePlayer(active_player)
{

}

void Game::newGame(const int &game_type)
{
    switch(game_type) {
    case 1:
        this->promotionTest();
        break;
    case 2:
        this->castlingTest();
        break;
    default:
        this->normalGame();
        break;
    }
}

void Game::castlingTest()
{
    // Clean board
    this->board = Board();

    // Kings
    this->board.addPiece(4, KING, WHITE);
    this->board.addPiece(60, KING, BLACK);

    // Rooks
    this->board.addPiece(0, ROOK, WHITE);
    this->board.addPiece(7, ROOK, WHITE);
    this->board.addPiece(56, ROOK, BLACK);
    this->board.addPiece(63, ROOK, BLACK);

    // Attack one of the fields
    this->board.addPiece(6, 1, BISHOP, BLACK);

    // Set active player and calculate possible moves
    this->activePlayer = WHITE;
    this->updateAllMoves();
}

void Game::normalGame()
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

void Game::promotionTest()
{
    // Clean board
    this->board = Board();

    // Kings
    this->board.addPiece(4, KING, WHITE);
    this->board.addPiece(60, KING, BLACK);

    // Promotion pawn
    this->board.addPiece(2, 6, PAWN, WHITE);
    this->board.addPiece(6, 1, PAWN, BLACK);

    // Extra piece (for promotion via capturing)
    this->board.addPiece(1, 7, KNIGHT, BLACK);

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
    // TODO: implement check, castling only allowed if fields in between not attacked.

    std::map<unsigned int, std::vector<Move> > moves;

    // Compute all potential moves
    for(Tile* t : this->board.getTiles()) {
        if(t->isOccupied() && this->getActivePlayer() == t->getPiece()->getColor()) {
            moves[t->getPosition()] = t->getPiece()->calculateMoves(this->getBoard());
        }
    }

    // Check castling moves - TODO not working yet
    for(auto &movesOfPiece : moves) {
        if(this->getBoard()->getTile(movesOfPiece.first)->isOccupied() &&
                this->getBoard()->getTile(movesOfPiece.first)->getPiece()->getType() == KING) {
            for(vector<Move>::iterator it=movesOfPiece.second.begin(); it!=movesOfPiece.second.end(); it++) {
                if((*it).getMoveType() == MT_CASTLING) {
                    if(movesOfPiece.first < (*it).getCastlingRookPosition()) {
                        for(unsigned int i=movesOfPiece.first + 1; i<(*it).getCastlingRookPosition(); i++) {
                            if(this->getBoard()->getTile(i)->tileUnderAttack(this->getBoard(), this->activePlayer)) {
                                // Castling not allowed; field in between under attack
                                movesOfPiece.second.erase(it);
                                break;
                            }
                        }
                    } else {
                        for(unsigned int i=movesOfPiece.first - 1; i>(*it).getCastlingRookPosition(); i--) {
                            if(this->getBoard()->getTile(i)->tileUnderAttack(this->getBoard(), this->activePlayer)) {
                                // Castling not allowed; field in between under attack
                                movesOfPiece.second.erase(it);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // Testing
    vector<string> attackedTiles;
    vector<string> occupiedTiles;
    for(Tile* t : this->board.getTiles()) {
        if(t->isOccupied()) occupiedTiles.push_back(t->getPositionString());
        if(t->tileUnderAttack(this->getBoard(), this->activePlayer)) attackedTiles.push_back(t->getPositionString());
    }
    cout << "Occupied tiles: ";
    for(auto &s : occupiedTiles) cout << s << " ";
    cout << endl;
    cout << "Attacked tiles: ";
    for(auto &s : attackedTiles) cout << s << " ";
    cout << endl << endl;

//    // Check whether king is currently in check position
//    for(auto &p : this->getBoard()->getPieces()) {
//        if(p->getColor() == this->activePlayer && p->getType() == KING && p->getTile()->tileUnderAttack(this->getBoard())) {
//            // King check!
//            for(auto &movesOfPiece : moves) {
//                // Loop through all pieces
//                for(vector<Move>::iterator it=movesOfPiece.second.begin(); it!=movesOfPiece.second.end(); it++) {
//                    // Perform virtual move
//                    Game virtualGame(*this);
//                    if((*it).getMoveType() == MT_PROMOTION) {
//                        // TODO deal with this
//                    } else {
//                        virtualGame.move(movesOfPiece.first, (*it).get());
//                    }

//                    // Check check status
//                    if(virtualGame.getBoard()->getTile(p->getTile()->getPosition())->tileUnderAttack(virtualGame.getBoard())) {
//                        // Move not allowed
//                        //moves2[movesOfPiece.first].push_back((*it));
//                        movesOfPiece.second.erase(it);
//                    }
//                }
//            }
//            break;
//        }
//    }

    // Return
    this->moves = moves;
}

enum MoveType Game::move(const unsigned int &from, const unsigned int &to, const PromotionType &pt)
{
    for(auto &m : this->getMoves(from)) {
        if(m.get() == to) {
            // Move possible

            // Check pawn double moves (for En Passant capturing)
            if(this->getBoard()->getTile(from)->getPiece()->getType() == PAWN) {
                Pawn* p = static_cast<Pawn*>(this->getBoard()->getTile(from)->getPiece().get());
                if(m.getMoveType() == MT_PAWNJUMP) {
                    p->setJustMovedDouble(true);
                } else {
                    p->setJustMovedDouble(false);
                }
            }

            // Perform move
            switch(m.getMoveType()) {
            case MT_PROMOTION:
                switch(pt) {
                case PT_QUEEN:
                    this->getBoard()->addPiece(to, QUEEN, this->getBoard()->getTile(from)->getPiece()->getColor());
                    break;
                case PT_ROOK:
                    this->getBoard()->addPiece(to, ROOK, this->getBoard()->getTile(from)->getPiece()->getColor());
                    break;
                case PT_BISHOP:
                    this->getBoard()->addPiece(to, BISHOP, this->getBoard()->getTile(from)->getPiece()->getColor());
                    break;
                case PT_KNIGHT:
                    this->getBoard()->addPiece(to, KNIGHT, this->getBoard()->getTile(from)->getPiece()->getColor());
                    break;
                default:
                    throw invalid_argument("Promotion type unknown.");
                    break;
                }
                this->getBoard()->getTile(from)->clearPiece();
                break;
            case MT_CASTLING:
                // Move king
                this->getBoard()->getTile(to)->setPiece(this->getBoard()->getTile(from)->getPiece());
                this->getBoard()->getTile(from)->clearPiece();
                // Move rook
                if(this->getBoard()->getTile(to)->getX() == 1) {
                    this->getBoard()->getTile(to+1)->setPiece(this->getBoard()->getTile(to-1)->getPiece());
                    this->getBoard()->getTile(to-1)->clearPiece();
                } else {
                    this->getBoard()->getTile(to-1)->setPiece(this->getBoard()->getTile(to+1)->getPiece());
                    this->getBoard()->getTile(to+1)->clearPiece();
                }
                break;
            case MT_ENPASSANT:
                // Capture opponent pawn
                if(this->getBoard()->getTile(from)->getPiece()->getColor() == WHITE) {
                    this->getBoard()->getTile(to-8)->clearPiece();
                } else {
                    this->getBoard()->getTile(to+8)->clearPiece();
                }
            default:
                this->getBoard()->getTile(to)->setPiece(this->getBoard()->getTile(from)->getPiece());
                this->getBoard()->getTile(from)->clearPiece();
                break;
            }



            // Update game
            this->getBoard()->getTile(to)->getPiece()->setMoved();
            this->activePlayer = this->activePlayer==WHITE ? BLACK : WHITE;
            this->updateAllMoves();
            return m.getMoveType();
        }
    }

    return MT_INVALID;
}

MoveType Game::getMoveType(const unsigned int &from, const unsigned int &to)
{
    for(auto &m : this->getMoves(from)) {
        if(m.get() == to) {
            return m.getMoveType();
        }
    }
    return MT_INVALID;
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


