#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "MazeClasses.hpp"
using namespace std;

int main() {
    
    Game MazeGame("MAZE_01.txt");
    auto begin = chrono::steady_clock::now();
    while (MazeGame.checkGameOver() == 0) {
        MazeGame.showGameDisplay();
        MazeGame.readHumanPlay();
        MazeGame.updateRobots();
        MazeGame.updateGame();
    }

    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::seconds>(end - begin);
    MazeGame.showGameDisplay();
    _getch();

    /*
    gameOver(checkGameOver(maze), (int) elapsed.count(), "MAZE_" + maze_number + "_WINNERS.TXT"); // 30 x 10
    _getch();
    */

}

//menu 3) Winners, if empty say empty list, if not ask for maze number then show the list
//eletrical posts +, you can go into them but you stay where you were and die
//non eletrical posts * or robots R or r, you can't run into them
//robots become r when they go to R or *, but stay dead in their place if they go to +
//if H reaches O, then O becomes H and game ends
//rules in RULES.txt
// 
//===========CLASSES======================================================
//Post
//Maze
//Player
//Robot
//Game
