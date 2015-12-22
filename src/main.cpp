#include "config.h"

// Include standard libraries
#include <iostream>
#include <utility>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QApplication>
    #include "chessgame.h"
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

    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;

    Board b(1);

    cout << b << endl;

    return 0;
#endif
}
