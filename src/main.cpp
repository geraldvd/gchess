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

    // Setup game
    Game g;
    //g.init();
    Piece * p1 = new King(0,0,1);
    Piece * p2 = new Queen(5,0,-1);
    Piece * p3 = new Pawn(5,1,-1);
    Piece * p4 = new Pawn(2,4,1);
    Piece * p5 = new Knight(6,5, 1);
    g.addWhitePiece(p1);
    g.addBlackPiece(p2);
    g.addBlackPiece(p3);
    g.addWhitePiece(p4);
    g.addWhitePiece(p5);
    g.updateAllMoves();

    // Position initial pieces
    for(auto &p : g.getWhitePieces()) {
        cb.addPiece(p);
        //qDebug() << QString::fromStdString(p->getType()) <<" (white) -> " << QString::fromStdString(p->getLetterPosition()) << endl;
    }
    for(auto &p : g.getBlackPieces()) {
        cb.addPiece(p);
        //qDebug() << QString::fromStdString(p->getType()) <<" (black) -> " << QString::fromStdString(p->getLetterPosition()) << endl;
    }

    //cb.highlightPossibleMove(3,5);
    cb.highlightPossibleMoves(g.getBlackPieces().at(0));

    cb.show();
    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;

    Game g;
    g.init();

    Piece *p = g.getWhitePieces().at(0);

    qDebug() << g.isValidMove(p, pair<int,int>(0,1)) << ", type=" << QString::fromStdString(p->getType()) << ", position=(" << p->getPosition().first << ", " << p->getPosition().second << ")" << endl;

    for(auto &i : p->getMoves()) {
        qDebug() << i.first << ", " << i.second << endl;
    }

    return 0;
#endif
}
