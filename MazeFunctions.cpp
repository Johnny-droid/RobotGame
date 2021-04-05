#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

vector<vector<char>> readFile(string filename) {
    // extract file and convert into vector of vector type (MAZE_XX.txt)
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "File not found";
        return {{'e'}};
    }

    vector<vector<char>> maze = {};
    string line;
    vector<char> row;
    char ch;
    while (getline(file, line)) {
        row = {};
        for (int i = 0; i < line.size(); i++) {
            ch = line[i];
            row.push_back(ch);
            
        }
        maze.push_back(row);
    }
    file.close();
    return maze;
}

void showMaze(vector<vector<char>> v) { 
    // prints out the maze
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
           cout << v[i][j]; 
        }      
        cout << endl;
    }
}

int menu() {
    // returns 0 Exit, 1 Rules, 2 Play
    int x;
    cout << "1) Rules \n2)Play \n0)Exit\n";
    do {
        cout << "Enter option: ";
        cin >> x;
        if ((x != 0 && x != 1 && x != 2) || cin.fail()) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid input!\n";
        }
    } while (x != 0 && x != 1 && x != 2);
    return x;
}

/*
vector<vector<int>> getRobotsXY(vector<vector<char>> maze) {
    // returns a vector with the robot coordinates
}

void updateRobotsXY(vector<vector<int>> &v, int x, int y) {
    //updates the robots vector with new positions according to the new Human position

}

int checkGameOver(vector<vector<char>> maze) {
    // check whether there is an 'h' or if there are no 'R' -> GAME OVER
    // 0 - continue, 1 - robots win, 2 - hero/human wins

}

void GameOver(int x, int time) {
    // check if it won, and if so
    // ask the name
    // sort the winning times

}





void rules() {
    // prints rules
}

void clean() {
    // cleans terminal

} 
*/