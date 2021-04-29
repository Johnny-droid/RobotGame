#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "MazeFunctions.cpp"
using namespace std;

int main() {
    vector<vector<char>> maze;
    vector<vector<int>> coordinates_R;
    vector<int> coordinates_H;
    int menu_ctrl, end_ctrl;
    string maze_number;

    menu_ctrl = menu(); // returns 0 Exit, 1 Rules, 2 Play
    menu_loop();  //se houver problemas, vem aqui e cola a função
    
    maze_number = readMazeNumber();
    auto begin = chrono::steady_clock::now();
    maze = readFile("MAZE_" + maze_number + ".TXT");
    coordinates_R = getRobotsXY(maze);
    coordinates_H = getHumanXY(maze);
    while (checkGameOver(maze) == 0) {
        showMaze(maze);
        readHumanPlay(maze, coordinates_H);
        updateRobotsXY(coordinates_R, coordinates_H);
        updateMaze(maze, coordinates_R, coordinates_H);
    }
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::seconds>(end - begin);
    showMaze(maze);
    gameOver(checkGameOver(maze), (int) elapsed.count(), "MAZE_" + maze_number + "_WINNERS.TXT"); // 30 x 10
    _getch();

}

/*
1. Ctrl-z switch
2. Center and clean text in console
3. Deal case file not found
*/