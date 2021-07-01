using namespace std;

#include "Spielfeld.h"

void Spielfeld::spielfeld() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sFeld[i][j] = 0;
            sFeld_temp[i][j] = 0;
            visited[i][j] = false;
        }
    }
}

void Spielfeld::zeigen() {
    char startChar = 'A';
    char startChar2 = 'A';
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            if (i == 0 && j == 0) {
                cout << "  ";
            }
            else if (i == 0) {
                cout << startChar << " ";
                startChar++;
            }
            else  if (j == 0) {
                cout << startChar2 << " ";
                startChar2++;
            }
            else {
                if (sFeld_temp[i - 1][j - 1] == 8) {
                    cout << "+ ";
                }
                else if (sFeld[i - 1][j - 1] == 0) {
                    cout << ". ";
                }
                else if (sFeld[i - 1][j - 1] == 1) {
                    cout << "X ";
                }
                else if (sFeld[i - 1][j - 1] == 2) {
                    cout << "O ";
                }
            }
        }

        cout << "\n\n";
    }
}