// Include standard libraries
#include <string>
#include <iomanip>
#include <sstream>
#include <map>

// Include project files
#include "operators.h"

// Specify namespaces
using namespace std;

Move operator+(const Move &m, const unsigned int &i)
{
    return Move(m.getX() + i%8, m.getY() + (i-i%8)/8, m.getMovingPiece());
}

Move operator+(const unsigned int &i, const Move &m)
{
    return m+i;
}


std::ostream &operator<<(std::ostream &os, Board &b)
{
    // Board information top
    os << "Active player: " << b.getActivePlayer()->getColorString()
       <<
          ", Board status: " << b.getBoardStatusString() << endl;

    // Fill board rows
    map<int,stringstream> rows;
    int currentRow = 0;
    for(Tile *t : b.getTiles()) {
        if(t->getX() == 0) {
            rows[t->getY()] << currentRow+1 << "   ";
        }
        if(t->isOccupied()) {
            rows[t->getY()] << setw(3) << t->getPiece()->getTypeString(true);
        } else {
            rows[t->getY()] << setw(3) << "-";
        }
        if(t->getX() == NUM_TILES_X-1) {
            rows[t->getY()] << endl;
            currentRow++;
        }
    }

    // Return rows inverted (i.e., white below)
    for(map<int,stringstream>::reverse_iterator it=rows.rbegin(); it !=rows.rend(); it++) {
        os << (*it).second.str();
    }

    // Footer
    os << endl << "    ";
    char currentColumn = 'a';
    for(int i=0; i<NUM_TILES_X; i++) {
        os << setw(3) << currentColumn++;
    }

    return os;
}

bool operator==(const Move &m1, const Move &m2)
{
    if(m1.getX() != m2.getX() || m1.getY() != m2.getY() || m1.getMovingPiece() != m2.getMovingPiece() ||
            m1.getMoveType() != m2.getMoveType() || m1.getCastlingRookPosition() != m2.getCastlingRookPosition()) {
        return false;
    }
    return true;
}

bool operator==(const Field &f1, const Field &f2)
{
    return f1.getX()==f2.getX() && f1.getY()==f2.getY();
}

bool operator!=(const Field &f1, const Field &f2)
{
    return f1.getX()!=f2.getX() || f1.getY()!=f2.getY();
}

ostream &operator<<(ostream &os, Board *b)
{
    return operator<<(os, *b);
}
