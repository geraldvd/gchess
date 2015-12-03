#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>


class Piece
{
public:
    Piece(int x, int y);
    std::vector<std::pair<int,int> > getMoves() const;
    void setMoves(const std::vector<std::pair<int, int> > & moves);

    std::pair<int, int> getPosition() const;
    void setPosition(const std::pair<int, int> & p);

private:
    std::pair<int,int> position;
    std::vector<std::pair<int,int> > moves;

protected:

protected:
    virtual void populateMoves() = 0;

    std::vector<std::pair<int, int> > movesOnBoard(std::vector<std::pair<int, int> > moves);

};

#endif // PIECE_H
