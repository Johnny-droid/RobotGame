#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "MazeClasses.hpp"
using namespace std;

int main() {
    int menu_ctrl; 
	string maze_number;
    bool replay_ctrl;

    do {
        showTitle();

        do {
            menu_ctrl = selectOption() ; // returns 0 Exit, 1 Rules, 2 Play, 3 Winners
            if (menu_ctrl == 0) {
                exit;
            }
            else if (menu_ctrl == 1) {
                printRules();
                showTitle();
            }
            else if (menu_ctrl == 2) {
                maze_number = readMazeNumber();
                if (maze_number == "0") {
                    menu_ctrl = 0;
                    showTitle();
                }
                else {
                    Game TestGame("MAZE_" + maze_number + ".TXT");
                    while (!TestGame.isValid()) {
                        maze_number = readMazeNumber(); //?????
                        if (maze_number == "0") {
                            menu_ctrl = 0;
                            showTitle();
                            break;
                        }
                        Game TestGame("MAZE_" + maze_number + ".TXT");
                    }
                }
            }
            else if (menu_ctrl == 3) {
                string leaderboard_number = readLeaderboardNumber();
                if (leaderboard_number == "0") {
                    menu_ctrl = 0;
                    showTitle();
                }
                else {
                    printLeaderBoard("MAZE_" + leaderboard_number + "_WINNERS.TXT");  
                    showTitle();
                }
            }
        } while (menu_ctrl != 2);
        
        Game MazeGame("MAZE_" + maze_number + ".TXT");
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
        gameOver(MazeGame.checkGameOver(), elapsed.count(), "MAZE_" + maze_number + "_WINNERS.TXT");
        replay_ctrl = replay(); 

    } while(replay_ctrl);
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
