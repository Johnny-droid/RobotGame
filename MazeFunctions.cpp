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

void showMaze(const vector<vector<char>> &v) { 
    // prints out the maze
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
           cout << v[i][j]; 
        }      
        cout << endl;
    }
}

void showCoordinates_R(const vector<vector<int>> &v) { 
    // prints out the the coordinates of the robots. Only used for development.
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
           cout << v[i][j] << ", "; 
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


vector<vector<int>> getRobotsXY(const vector<vector<char>> &maze) {
    // returns a vector with the robot coordinates
    vector<vector<int>> v = {};
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'R') {
                v.push_back({i, j}); // i is y and j is x
            }
        }
    }
    return v;
}

void updateRobotsXY(vector<vector<int>> &v, const vector<int> &h) {
    //updates the robots vector with new positions according to the new Human position
    // x and y - human    Rx and Ry - robot
    for (int i = 0; i < v.size(); i++) {
        int &Rx = v[i][1], &Ry = v[i][0];
        int x = h[1], y = h[0];
        if (Rx == x && Ry < y) {
            Ry++;
        } else if (Rx == x && Ry > y) {
            Ry--;
        } else if (Ry == y && Rx < x) {
            Rx++;
        } else if (Ry == y && Rx > x) {
            Rx--;
        } else if (Rx < x && Ry < y) {
            Rx++;
            Ry++;
        } else if (Rx < x && Ry > y) {
            Rx++;
            Ry--;
        } else if (Rx > x && Ry < y) {
            Rx--;
            Ry++;
        } else if (Rx > x && Ry > y) {
            Rx--;
            Ry--;
        }
    }
}

void updateMaze(vector<vector<char>> &maze, vector<vector<int>> &v, const vector<int> &h) {
    //updates the maze according to the new information provided by the user and
    // the calculations of the robots new positions

    // remove the 'R's and the 'H' from the maze, since we are going to assign new positions to them
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'R' || maze[i][j] == 'H') {
                maze[i][j] = ' ';
            }
        }
    }

    //check for robot collisions with fences
    for (int i = 0; i < v.size(); i++) {
        if (maze[v[i][0]][v[i][1]] == '*') {
            maze[v[i][0]][v[i][1]] = 'r';
            v.erase(v.begin() + i);
            i--;
        }
    }

    //check for robots collisions (robots with equal coordinates)
    for (int i = 0; i < v.size()-1; i++) {
        bool equal_found = false;
        for (int j = i+1; j < v.size(); j++) {
            if (v[i] == v[j]) {
                v.erase( v.begin() + j);
                j--;
                equal_found = true;
            }
        }
        if (equal_found) {
            maze[v[i][0]][v[i][1]] = 'r';
            v.erase(v.begin() + i);
            i--;
        }
    }

    // redraw robots (think of joining with the loop below)
    for (int i = 0; i < v.size(); i++) {
        maze[v[i][0]][v[i][1]] = 'R';
    }

    //check if the human is alive...
    // killed by robot
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == h) {
            maze[h[0]][h[1]] = 'h';
            break;
        }
    }
    //killed by eletric fence
    if (maze[h[0]][h[1]] == '*') {
        maze[h[0]][h[1]] = 'h';
    }

}

int checkGameOver(const vector<vector<char>> &maze) {
    // check whether there is an 'h' or if there are no 'R' -> GAME OVER
    // 0 - continue, 1 - robots win, 2 - hero/human wins
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'R') {
                return 0;
            }
            if (maze[i][j] == 'h') {
                return 1;
            }
        }
    }
    return 2;

}

void GameOver(int x, int time, string filename) {
    // check if it won, and if so
    // ask the name
    // sort the winning times
    // not finished yet!!
    if (x == 2) {
        ifstream file;
        file.open(filename);
        if (!file.is_open()) {
            cout << "File not found" << endl;
        } else {
            string winner = readName();
            string line, player;
            int time_players;
            size_t pos;
            getline(file, line);   // ignore the first 2 lines of the file
            getline(file, line);   // Lines: (Player - Time) and (---------)
            while (getline(file, line)) {
                player = line.substr(0, 15);
                pos = line.find('-');
                time_players = (int) strip(line.substr(pos+1));   //strip time
            }

            file.close();
        }
    }
}

// sorting function to sort the times of the winners
void bubbleSort(vector<int> &v) {
    int aux;
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < v.size()-1; i++) {
            if (v[i] > v[i+1] ) {
                change = true;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
    }
}

string readName() {
    // reads the name of the player, but it can only have 15 characters!!!
    // if smaller, fills the name with whitespace
    string name;
    do {
        cout << "Enter your name: ";
        cin >> name;
        if ( name.length() > 15 || cin.fail()) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid input!\n";
        }
    } while (name.length() > 15);

    while (name.length() < 15) {
        name += ' ';
    }
    return name;    
}



/*
void rules() {
    // prints rules
}

void clean() {
    // cleans terminal

} 
*/

string strip(string &str) {
    // removes the leading and trailing whitespaces of a string
    size_t start = str.find_last_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return str.substr(start, end-start+1);
}