#include "config.h"

// Include standard libraries
#include <iostream>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QtWidgets/QApplication>
    #include <chessboard.h>
#endif

#include <QtCore/QDebug>

// Include project libraries

// Namespaces
using namespace std;

int main(int argc, char **argv) {
#ifdef WITH_GRAPHICS
    // Initialize Qt application
    QApplication a(argc,argv);

    Chessboard cb;
    cb.show();

    return a.exec();
#else
    qDebug() << "Running from terminal!" << endl;

    return 0;
#endif
}
