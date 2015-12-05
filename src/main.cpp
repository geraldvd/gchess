#include "config.h"

// Include standard libraries
#include <iostream>
#include <utility>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QtWidgets/QApplication>
    #include <chessboard.h>
#endif

#include <QtCore/QDebug>

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
    Chessboard cb;
    cb.newGame();

//    // Setup game
//    Game g;
//    g.init();

//    // Position initial pieces
//    for(auto &p : g.getPieces()) {
//        cb.addPiece(p);
//    }


//    //cb.highlightPossibleMoves(g.getPieces().at(15));

    cb.show();
//    cb.movePiece(g.getPieces().at(0)->getPosition(), g.getPieces().at(0)->getPosition() + Field(0,1));
    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;

    Game g;
    g.init();

    return 0;
#endif
}
