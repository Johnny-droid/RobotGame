#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "MazeClasses.hpp"
using namespace std;

int main() {
    int a = 1, b = 3;
    char c = 'H';
    Player p1(a, b, c);
    p1.show();
    
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
