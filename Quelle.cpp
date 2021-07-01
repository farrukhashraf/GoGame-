#include <iostream>
#include <conio.h>

#include "GoGame.h"

using namespace std;

int main() {
    cout << "Welcome to Go Spiel";
    GoGame spiel;
    spiel.setSpielart();
    spiel.setSpieler();
    spiel.spielfeld.zeigen();
    // men vs men
    if (spiel.spielart == 1) {
        while (true) {
            if (spiel.turn == 1) {
                if (spiel.skipSpieler1 == false)
                    cout << spiel.spieler1 << " turn" << endl;
                else {
                    spiel.turn = 2;
                    continue;
                }
                    
            }
            else {
                if (spiel.skipSpieler2 == false)
                    cout << spiel.spieler2 << " turn" << endl;
                else {
                    spiel.turn = 1;
                    continue;
                }
            }
            while (true) {
                char key = _getch();
                if (!spiel.playerOperation(key)) {
                    system("cls");
                    spiel.spielfeld.zeigen();
                    spiel.spielInfo();
                    break;
                }
                else {
                    system("cls");
                    spiel.spielfeld.zeigen();
                    spiel.spielInfo();
                }

            }
            if (spiel.checkGameEnd())
                return 0;
        }
    }
    else { // men vs AI
        while (true) {
            if (spiel.turn == 1) {
                if (spiel.skipSpieler1 == false)
                    cout << spiel.spieler1 << " turn" << endl;
                else {
                    spiel.turn = 2;
                    continue;
                }
            }
            else {
                if (spiel.skipSpieler2 == false)
                    cout << spiel.spieler2 << " turn" << endl;
                else {
                    spiel.turn = 1;
                    continue;
                }
            }
            while (true) {
                if (spiel.turn == 1) {
                    char key = _getch();
                    if (!spiel.playerOperation(key)) {
                        system("cls");
                        spiel.spielfeld.zeigen();
                        spiel.spielInfo();
                        break;
                    }
                    else {
                        system("cls");
                        spiel.spielfeld.zeigen();
                        spiel.spielInfo();
                    }
                }
                else { //AI turn
                    spiel.makeAIMove();
                    spiel.turn = 1;
                    system("cls");
                    spiel.spielfeld.zeigen();
                    spiel.spielInfo();
                    break;
                }
            }
        }
    }


    return 0;
}