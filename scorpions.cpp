#include <iostream>
#include "Spielfeld.h"
#include "GoGame.h"
using namespace std;

int main() {
    cout << "Go Spiel!" << endl;
    GoGame spiel;
    spiel.setSpielart();
    spiel.setSpieler();
    Spielfeld spielfeld;
    spielfeld.size = 19;
    spielfeld.spielfeld();
    spielfeld.zeigen();
    spiel.spielInfo();
    return 0;
}
