#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <vector>
#include <string>

// Typedef for chess field
typedef std::pair<int,int> Field;

class Piece
{
public:
    Piece(int x, int y, int c);

    std::string getType() const;
    int getColor() const;

    std::vector<Field> getMoves() const;
    std::vector<Field> getGlobalMoves() const;
    void setMoves(const std::vector<Field> & moves);

    Field getPosition() const;
    Field getGlobalPosition() const;
    std::string getLetterPosition() const;
    void setPosition(const Field & p);


    virtual std::vector<Field> findTheoreticalMoves() = 0;
    void findMoves();
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
