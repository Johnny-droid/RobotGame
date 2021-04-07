#include <iostream>
#include <vector>
#include <string>
#include "MazeFunctions.cpp"
using namespace std;

int main() {
    vector<vector<char>> maze;
    vector<vector<int>> coordinates_R;
    vector<int> coordinates_H;
    int menu_ctrl, end_ctrl;

    menu_ctrl = menu(); // returns 0 Exit, 1 Rules, 2 Play
    while (menu_ctrl != 2) {
        if (menu_ctrl == 0) {
            return 0;
        } else if (menu_ctrl == 1) {
            rules();
        }
        menu_ctrl = menu();
    }

    maze = readFile("MAZE_01.txt");
    coordinates_R = getRobotsXY(maze);
    coordinates_H = getHumanXY(maze);
    while (checkGameOver(maze) == 0) {
        showMaze(maze);
        readHumanPlay(maze, coordinates_H);
        updateRobotsXY(coordinates_R, coordinates_H);
        updateMaze(maze, coordinates_R, coordinates_H);
    }
    showMaze(maze);
    gameOver(checkGameOver(maze), 700, "MAZE_01_WINNERS.txt");
    _getch();
    /*
    showCoordinates_R(coordinates_R);
    updateRobotsXY(coordinates_R, {6, 12});
    updateMaze(maze, coordinates_R, {6, 12});
    showMaze(maze);
    showCoordinates_R(coordinates_R);
    gameOver(2, 700, "MAZE_01_WINNERS.txt");
    */

}