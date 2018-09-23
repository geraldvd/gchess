#include <iostream>
using namespace std;

#include "../src/game/board/field.h"

int main(int argc, char* argv[]) {
    // Test constructors
    Field f1(7, 7);
    Field f2("H8");


    // Test getters
    cout << f1.get() << endl;
    cout << f2.getX() << ", " << f2.getY() << endl;


    return 0;
}
