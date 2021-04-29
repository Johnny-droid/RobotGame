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
    while (menu_ctrl != 2) {
        if (menu_ctrl == 0) {
            return 0;
        } else if (menu_ctrl == 1) {
            rules();
        }
        menu_ctrl = menu();
    }

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
1. Fix maze 1
2. Ctrl-z switch
3. Center and clean text in console
4. Deal case file not found
*/