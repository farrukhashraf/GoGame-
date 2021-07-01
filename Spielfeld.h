#include <iostream>
#include <string>
using namespace std;

class Spielfeld {
public:
    int sFeld[30][30];
    int sFeld_temp[30][30];
    bool visited[30][30];
    int size;
    void spielfeld();
    void zeigen();
};