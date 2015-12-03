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

    pair<int,int> a(1,2);
    pair<int,int> b(1,2);
    pair<int,int> c(2,1);

    qDebug() << int(a==b) << ", " << int(b==c) << endl;

    return 0;
#endif
}
