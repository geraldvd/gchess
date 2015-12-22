#include "config.h"

// Include standard libraries
#include <iostream>
#include <utility>

// Include Qt
#ifdef WITH_GRAPHICS
    #include <QApplication>
    #include "chessgame.h"
#else
    #include <iostream>
    #include <string>
    #include "gamemanager.h"
#endif

#include <QDebug>

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

    // Start game
    GameManager game;

    string position;
    do {
        cout << game.getBoard() << endl << endl;

        Field from, to;

        do{
            cout << "Move " << game.getBoard()->getActivePlayer()->getColorString() << ". Type coordinates from -> to." << endl;
            while(true) {
                try {
                    cout << "From: ";
                    cin >> position;
                    from = string2field(position);
                } catch(invalid_argument &e) {
                    cout << "Wrong coordinate; try again!" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                break;
            }

            while(true) {
                try {
                    cout << "To: ";
                    cin >> position;
                    to = string2field(position);
                } catch(invalid_argument &e) {
                    cout << "Wrong coordinate; try again!" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                break;
            }
        } while(game.move(from, to) == MS_INVALID);
        cout << endl;
    } while(game.getBoard()->getBoardStatus() != BS_CHECKMATEBLACK && game.getBoard()->getBoardStatus() != BS_CHECKMATEWHITE &&
            game.getBoard()->getBoardStatus() != BS_STALEMATE);


    return 0;
#endif
}
