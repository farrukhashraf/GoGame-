#include "GoGame.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void GoGame::setSpielart() {
    // let player choose option
    cout << "W<ehlen Sie Spielart:" << endl;
    cout << "1. Mensch V/S Mensch" << endl;
    cout << "2. Mensch V/S KI" << endl;
    cout << "Waehlen Sie option 1, 2" << endl;
    cin >> spielart;
}

void GoGame::spielInfo() {
    cout << "Punkestand:" << endl;
    cout << "Spieler1: (" << spieler1 << "): " << spieler1Point << endl;
    cout << "Spieler2: (" << spieler2 << "): " << spieler2Point << endl;
    cout << "Press H to skip" << endl;
    cout << "\n\n";
}

void GoGame::setSpieler() {
    if (spielart == 1) {
        cout << "Enter Spieler 1 Name:" << endl;
        cin >> spieler1;
        cout << "Enter Spieler 2 Name:" << endl;
        cin >> spieler2;
    }
    else if (spielart == 2) {
        cout << "Enter Spieler  Name:" << endl;
        cin >> spieler1;
        spieler2 = "KI";
    }
    else {
        cout << "Invalid Option" << endl;
    }

    spieler1Point = 0;
    spieler2Point = 0;
}

bool GoGame::playerOperation(char key) {
    bool ifContinue = true;
    switch (key) {
    case 'w':
        if (x - 1 >= 0) {
            x--;
            spielfeld.sFeld_temp[x][y] = 8;
            spielfeld.sFeld_temp[x + 1][y] = 0;
        }
        break;
    case 's':
        if (x + 1 < spielfeld.size) {
            x++;
            spielfeld.sFeld_temp[x][y] = 8;
            spielfeld.sFeld_temp[x - 1][y] = 0;
        }
        break;
    case 'a':
        if (y - 1 >= 0) {
            y--;
            spielfeld.sFeld_temp[x][y] = 8;
            spielfeld.sFeld_temp[x][y + 1] = 0;
        }
        break;
    case 'd':
        if (y + 1 < spielfeld.size) {
            y++;
            spielfeld.sFeld_temp[x][y] = 8;
            spielfeld.sFeld_temp[x][y - 1] = 0;
        }
        break;
    case ' ':
        if (spielfeld.sFeld[x][y] == 0) {
            if (turn == 1) {
                spielfeld.sFeld[x][y] = 1;
                spieler1Point += updatePoints(turn);
                turn = 2;
            }
            else {
                spielfeld.sFeld[x][y] = 2;
                spieler2Point += updatePoints(turn);
                turn = 1;
            }

            ifContinue = false;
        }
        break;
    case 'h':
        if (turn == 1)
            skipSpieler1 = true;
        else
            skipSpieler2 = true;
        ifContinue = false;
        break;
    }

    return ifContinue;
}


bool GoGame::isValid(int x, int y) {
    return x >= 0 && x < spielfeld.size && y >= 0 && y < spielfeld.size;
}


int GoGame::updatePoints(int turn) {
    int nextTurn;
    if (turn == 1) {
        nextTurn = 2;
    }
    else {
        nextTurn = 1;
    }

    int capturedLiberties = 0;
    vector<pair<int, int>> toRollBack;
    for (int i = 0; i < spielfeld.size; i++) {
        for (int j = 0; j < spielfeld.size; j++) {
            if (spielfeld.sFeld[i][j] == nextTurn && spielfeld.visited[i][j] == false) {
                int count = calculateCapturedLiberties(i, j, nextTurn);
                if (count != -1) {
                    capturedLiberties += count;
                }
                else {
                    toRollBack.push_back(make_pair(i, j));
                }
            }
        }
    }

    for (int i = 0; i < toRollBack.size(); i++) {
        updateVisitedPoints(toRollBack[i].first, toRollBack[i].second, nextTurn, false);
    }
    return capturedLiberties;
}

int GoGame::calculateCapturedLiberties(int x, int y, int symbol) {
    int DIR[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    spielfeld.visited[x][y] = true;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nr = x + DIR[i][0];
        int nc = y + DIR[i][1];
        if (isValid(nr, nc) && spielfeld.sFeld[nr][nc] == 0) {
            return -1;
        }

        if (isValid(nr, nc) && spielfeld.sFeld[nr][nc] == symbol && spielfeld.visited[nr][nc] == false) {
            int connectedCount = calculateCapturedLiberties(nr, nc, symbol);
            if (connectedCount == -1) {
                return -1;
            }
            else {
                count += connectedCount;
            }
        }
    }

    return count + 1;
}

void GoGame::updateVisitedPoints(int x, int y, int symbol, bool flag) {
    int DIR[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    spielfeld.visited[x][y] = flag;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nr = x + DIR[i][0];
        int nc = y + DIR[i][1];
        if (isValid(nr, nc) && spielfeld.sFeld[nr][nc] == symbol && spielfeld.visited[nr][nc] != flag) {
            updateVisitedPoints(nr, nc, symbol, flag);
        }
    }
}

void GoGame::makeAIMove() {
    for (int i = 0; i < spielfeld.size; i++) {
        for (int j = 0; j < spielfeld.size; j++) {
            if (spielfeld.sFeld[i][j] == 0) {
                spielfeld.sFeld[i][j] = 2;
                int points = updatePoints(2);
                if (points <= 0) {
                    updateVisitedPoints(i, j, 1, false);
                    spielfeld.sFeld[i][j] = 0;
                }
                else {
                    spieler2Point += points;
                    return;
                }
            }
        }
    }

    for (int i = 0; i < spielfeld.size; i++) {
        for (int j = 0; j < spielfeld.size; j++) {
            if (spielfeld.sFeld[i][j] == 0 && checkNeighbours(1, i, j)) {
                spielfeld.sFeld[i][j] = 2;
                int points = updatePoints(1);
                if (points > 0) {
                    updateVisitedPoints(i, j, 2, false);
                    spielfeld.sFeld[i][j] = 0;
                }
                else {

                    return;
                }
            }
        }
    }

    // if no points on any move make random move Check
    while (true) {
        srand(time(NULL));
        int x = rand() % 19;
        int y = rand() % 19;
        if (spielfeld.sFeld[x][y] == 0) {
            spielfeld.sFeld[x][y] = 2;
            return;
        }
    }

    skipSpieler2 = true;
}

bool GoGame:: checkNeighbours(int symbol, int row, int col) {
    int DIR[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    for (int i = 0; i < 4; i++) {
        int nr = row + DIR[i][0];
        int nc = col + DIR[i][1];
        if (isValid(nr, nc) && spielfeld.sFeld[nr][nc] == symbol) {
            return true;
        }
    }

    return false;
}

bool GoGame::checkGameEnd() {
    if (skipSpieler1 == true && skipSpieler2 == true) {
        cout << "Game ended" << endl;
        if (spieler1Point > spielart) {
            cout << spieler1 << " Won" << endl;
        }
        else {
            cout << spieler2 << " Won" << endl;
        } 
        
        return true;
    }

    return false;
}