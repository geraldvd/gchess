#include "config.h"

// Include standard libraries
#include <iostream>
#include <utility>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QApplication>
    #include "chessgame.h"
    #include "piece/queen.h"
#else
    #include <game.h>
#endif

#include <QDebug>

// Include project libraries
#ifdef WITH_GAME
    #include "game.h"
#endif

// Namespaces
using namespace std;

int main(int argc, char **argv) {
#ifdef WITH_GRAPHICS
    // Initialize Qt application
    QApplication a(argc,argv);

    // Initialize board
    ChessGame chess;
    chess.show();

//    // Test
//    Board b;
//    //Tile t("A8");
//    auto p = new Queen(b.getTile(62)->getPosition(), BLACK);
//    b.getTile(62)->setPiece(p);
//    qDebug() << b.getTile(62)->getPosition() << endl;
//    qDebug() << b.getTile(62)->isOccupied() << endl;
//    qDebug() << b.getTile(62)->getPiece()->getType() << endl;

    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;

    Board b;
    cout << b.getTile(1).getPositionString() << endl;

    return 0;
#endif
}
