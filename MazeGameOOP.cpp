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
            if (menu_ctrl == 0) {   // exit
                return 0;  // exits the game
            }
            else if (menu_ctrl == 1) {   //rules
                printRules();  //prints the rules
                showTitle(); 
            }
            else if (menu_ctrl == 2) {    //play
                maze_number = readMazeNumber();  
                if (maze_number == "0") {   // goes back to the main menu
                    menu_ctrl = 0;
                    showTitle();
                }
                else {
                    Game TestGame("MAZE_" + maze_number + ".TXT");   // creates the game
                    while (!TestGame.isValid()) {                    // builds a test game to see if it's valid. Otherwise it keeps 
                        maze_number = readMazeNumber();              // asking for the maze number again
                        if (maze_number == "0") {
                            menu_ctrl = 0;
                            showTitle();
                            break;
                        }
                        Game TestGame("MAZE_" + maze_number + ".TXT");
                    }
                }
            }
            else if (menu_ctrl == 3) {  //winners
                string leaderboard_number = readLeaderboardNumber();  // return the number in the same format as readMazeNumber()  (ex: 01  or 24)
                if (leaderboard_number == "0") {   // goes back to the main menu
                    menu_ctrl = 0;
                    showTitle();
                }
                else {
                    printLeaderBoard("MAZE_" + leaderboard_number + "_WINNERS.TXT");  // shows the leaderboard of the maze of the corresponding number
                    showTitle();
                }
            }
        } while (menu_ctrl != 2);
        
        Game MazeGame("MAZE_" + maze_number + ".TXT");  // builds the game
        auto begin = chrono::steady_clock::now();   // starts counting the time. When the cycle ends, the game has finished
        while (MazeGame.checkGameOver() == 0) {   // 0 -> continue,    1 -> robots win,   2 -> hero/human wins
            MazeGame.showGameDisplay();          
            MazeGame.readHumanPlay();
            MazeGame.updateRobots();
            MazeGame.updateGame();
        }

        auto end = chrono::steady_clock::now();  // stops counting the time
        auto elapsed = chrono::duration_cast<std::chrono::seconds>(end - begin);   // calculates the time (in seconds) 
        MazeGame.showGameDisplay();  
        gameOver(MazeGame.checkGameOver(), elapsed.count(), "MAZE_" + maze_number + "_WINNERS.TXT");  // shows and records your time if you won. 
        replay_ctrl = replay();   // asks if you want to exit the game or play once again

    } while(replay_ctrl);
}

