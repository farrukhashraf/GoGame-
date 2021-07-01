#include <iostream>
#include "Spielfeld.h"
using namespace std;

class GoGame {
public:
    int spielart;
    string spieler1;
    string spieler2;
    int spieler1Point;
    int spieler2Point;
    bool skipSpieler1;
    bool skipSpieler2;
    Spielfeld spielfeld;
    int x;
    int y;
    int turn;

    GoGame() {
        spielfeld.size = 19;
        spielfeld.spielfeld();
        x = 8;
        y = 8;
        turn = 1;
        skipSpieler1 = false;
        skipSpieler2 = false;
    }
    void setSpielart();
    void setSpieler();
    void spielInfo();
    bool playerOperation(char key);
    bool isValid(int x, int y);
    int updatePoints(int turn);
    void makeAIMove();
    void updateVisitedPoints(int x, int y, int symbol, bool flag);
    int calculateCapturedLiberties(int x, int y, int symbol);
    bool checkNeighbours(int symbol, int row, int col);
    bool checkGameEnd();
};