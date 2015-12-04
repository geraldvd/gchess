#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>


class Piece
{
public:
    Piece(int x, int y, int c);

    std::string getType() const;
    int getColor() const;

    std::vector<std::pair<int,int> > getMoves() const;
    std::vector<std::pair<int,int> > getGlobalMoves() const;
    void setMoves(const std::vector<std::pair<int, int> > & moves);

    std::pair<int, int> getPosition() const;
    std::pair<int, int> getGlobalPosition() const;
    std::string getLetterPosition() const;
    void setPosition(const std::pair<int, int> & p);


    virtual void populateMoves() = 0;
private:
    std::pair<int,int> position;
    std::vector<std::pair<int,int> > moves;

protected:
    std::string type;
    int color;

protected:
    std::vector<std::pair<int, int> > movesOnBoard(std::vector<std::pair<int, int> > moves);


};

#endif // PIECE_H
