#include <iostream>
#include <conio.h>

#include "GoGame.h"

using namespace std;

int main() {
    cout << "Welcome to Go Spiel";
    GoGame spiel;
    // set the game type
    spiel.setSpielart();
    // set the player information
    spiel.setSpieler();
    // set the spielfeld
    spiel.spielfeld.zeigen();
    // men vs men
    if (spiel.spielart == 1) {
        while (true) {
            if (spiel.turn == 1) {// if turn of player 1
                if (spiel.skipSpieler1 == false)// if player skipped no turn for him
                    cout << spiel.spieler1 << " turn" << endl;
                else {
                    spiel.turn = 2;// change the turn
                    continue;
                }
                    
            }
            else {// if turn of player 2
                if (spiel.skipSpieler2 == false)// if player skipped no turn for him
                    cout << spiel.spieler2 << " turn" << endl;
                else {
                    spiel.turn = 1;// change the turn
                    continue;
                }
            }
            while (true) {
                char key = _getch();// take input for the move
                if (!spiel.playerOperation(key)) {// check player operation
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
        while (true) {// if turn of player 1
            if (spiel.turn == 1) {
                if (spiel.skipSpieler1 == false) // if player skipped no turn for him
                    cout << spiel.spieler1 << " turn" << endl;
                else {
                    spiel.turn = 2;// change the turn
                    continue;
                }
            }
            else {// KI turn
                if (spiel.skipSpieler2 == false)
                    cout << spiel.spieler2 << " turn" << endl;
                else {
                    spiel.turn = 1;
                    continue;
                }
            }
            while (true) {
                if (spiel.turn == 1) {
                    char key = _getch();// take input for the move
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
                    spiel.makeAIMove();// make move if AI
                    spiel.turn = 1; // change the turn
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