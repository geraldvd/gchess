// Include standard libraries
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

// Include project files
#include "operators.h"

// Specify namespaces
using namespace std;

Tile operator+(const Tile &t1, const Tile &t2)
{
    return Tile(t1.getPosition()+ t2.getPosition());
}

bool operator==(const Tile &t1, const Tile &t2)
{
    return t1.getPosition()==t2.getPosition();
}

bool operator<(const Tile &t1, const Tile &t2)
{
    return t1.getPosition() < t2.getPosition();
}

bool operator>(const Tile &t1, const Tile &t2)
{
    return t1.getPosition() > t2.getPosition();
}

Move operator+(const Move &m, const unsigned int &i)
{
    return Move(m.getX() + i%8, m.getY() + (i-i%8)/8);
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
    vector<stringstream> rows(NUM_TILES_Y+1);
    int currentRow = 0;
    for(Tile *t : b.getTiles()) {
        if(t->getX() == 0) {
            rows.at(currentRow) << currentRow+1 << "   ";
        }
        if(t->isOccupied()) {
            rows.at(currentRow)<< setw(3) << t->getPiece()->getTypeString(true);
        } else {
            rows.at(currentRow) << setw(3) << "-";
        }
        if(t->getX() == NUM_TILES_X-1) {
            rows.at(currentRow++) << endl;
        }
    }

    // Return rows inverted (i.e., white below)
    for(vector<stringstream>::reverse_iterator it=rows.rbegin(); it !=rows.rend(); it++) {
        os << (*it).str();
    }

    // Footer
    os << endl << "    ";
    char currentColumn = 'a';
    for(int i=0; i<NUM_TILES_X; i++) {
        os << setw(3) << currentColumn++;
    }

    return os;
}
