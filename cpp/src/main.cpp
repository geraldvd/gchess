#include "config.h"

// Include standard libraries
#include <iostream>
#include <string>
#include <limits>

#ifdef WITH_QT
    #include <QApplication>
    #include "gui/chesswindow.h"
#else
    #include "board/field.h"
#endif

// Include project files
#include "gamemanager.h"

// Namespaces
using namespace std;

int main(int argc, char **argv) {
#ifdef WITH_QT
    // Initialize Qt application
    QApplication a(argc,argv);

    // Initialize board
    ChessWindow chessWindow;
    chessWindow.show();

    return a.exec();
#else
    // Start game
    GameManager game;

    string position;
    do {
        cout << game.getBoard() << endl << endl;

        Field from{0, 0}, to{0, 0};

        do{
            cout << "Move " << game.getBoard()->getActivePlayer()->getColorString() << ". Type coordinates from -> to." << endl;
            while(true) {
                try {
                    cout << "From: ";
                    cin >> position;
                    from = Field::string2field(position);
                } catch(invalid_argument &e) {
                    cout << "Wrong coordinate; try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                break;
            }

            while(true) {
                try {
                    cout << "To: ";
                    cin >> position;
                    to = Field::string2field(position);
                } catch(invalid_argument &e) {
                    cout << "Wrong coordinate; try again!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
