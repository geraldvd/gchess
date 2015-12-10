#include "config.h"

// Include standard libraries
#include <iostream>
#include <utility>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QtWidgets/QApplication>
    #include <chessgame.h>
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
    ChessGame chess;
    //Chessboard2 chess;
    chess.show();

//    Game g;
//    g.init();
//    for(auto &i : g.getPieces()) {
//        chess.addPiece(i->getPosition(), i->getColor(), i->getType());
//    }
//    chess.clearPieces();
//    g.init();
//    for(auto &i : g.getPieces()) {
//        chess.addPiece(i->getPosition(), i->getColor(), i->getType());
//    }
//    chess.show();


    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;
    return 0;
#endif
}
