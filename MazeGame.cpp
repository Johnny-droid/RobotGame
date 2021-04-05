#include <iostream>
#include <vector>
#include <string>
#include "MazeFunctions.cpp"
using namespace std;

int main() {
    vector<vector<char>> maze;
    int n;

    n = menu();
    maze = readFile("MAZE_01.txt");
    showMaze(maze);    
}