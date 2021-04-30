#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "MazeFunctions.cpp"
using namespace std;

int main() {
    vector<vector<char>> maze, error = {{'e'}};
    vector<vector<int>> coordinates_R;
    vector<int> coordinates_H;
    int menu_ctrl, end_ctrl;
    string maze_number;

    showTitle();

    do {
        menu_ctrl = menu(); // returns 0 Exit, 1 Rules, 2 Play
        if (menu_ctrl == 0) {
            return 0;
        }
        else if (menu_ctrl == 1) {
            rules();
        }
        if (menu_ctrl == 2) {
            
            maze_number = readMazeNumber();
            if (maze_number == "0") {
                menu_ctrl = 3;
            } else {
                maze = readFile("MAZE_" + maze_number + ".TXT");
                while (maze == error) {
                    maze_number = readMazeNumber(false);
                    if (maze_number == "0") {
                        menu_ctrl = 3;
                        break;
                    }
                    maze = readFile("MAZE_" + maze_number + ".TXT");
                } 
            } 
        }
    } while (menu_ctrl != 2);
    

    auto begin = chrono::steady_clock::now();
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
1. Deal case file not found
*/