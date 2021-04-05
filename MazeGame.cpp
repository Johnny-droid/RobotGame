#include <iostream>
#include <vector>
#include <string>
#include "MazeFunctions.cpp"
using namespace std;

int main() {
    vector<vector<char>> maze;
    vector<vector<int>> coordinates_R;
    int n;

    n = menu();
    maze = readFile("MAZE_01.txt");
    coordinates_R = getRobotsXY(maze);
    showCoordinates_R(coordinates_R);    
}