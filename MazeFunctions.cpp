#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

vector<vector<char>> readFile(string filename) {
    // extract file and convert into vector of vector type (MAZE_XX.txt)
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Maze not found!" << endl;
        return {{'e'}};
    }

    vector<vector<char>> maze = {};
    string line;
    vector<char> row;
    getline(file, line); //ignore first line;
    while (getline(file, line)) {
        row = {};
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
        }
        maze.push_back(row);
    }
    file.close();
    return maze;
}

void showTitle() {
    cout << "\n\n";
    cout << "\t\t\t _____   ____  ____   ____ _______  __          __     _____   _____" << endl;
    cout << "\t\t\t|  __ \\ / __ \\|  _ \\ / __ \\__   __| \\ \\        / /\\   |  __ \\ / ____|" << endl;
    cout << "\t\t\t| |__) | |  | | |_) | |  | | | |     \\ \\  /\\  / /  \\  | |__) | (___" << endl;
    cout << "\t\t\t|  _  /| |  | |  _ <| |  | | | |      \\ \\/  \\/ / /\\ \\ |  _  / \\___ \\ " << endl;
    cout << "\t\t\t| | \\ \\| |__| | |_) | |__| | | |       \\  /\\  / ____ \\| | \\ \\ ____) |" << endl;
    cout << "\t\t\t|_|  \\_\\\\____/|____/ \\____/  |_|        \\/  \\/_/    \\_\\_|  \\_\\_____/ " << endl;
    cout << endl;
}

string readMazeNumber(bool showText = true) {
    // Read the number of maze
    int n;
    string str;
    bool success = false;
    if (showText) {
        cout << "\n           ---------------------------------------------------------                                   " << endl;
        cout << "          | There are 6 distinct maze layouts, each of these with   |     There are more       _\\/_      " << endl;
        cout << "          | 10 versions featuring different starting positions for  |     robots like me      [____]     " << endl;
        cout << "          | the robots and yourself.                                |     on the last stages. |()()|     " << endl;
        cout << "          |                                                         |     Choose wisely.    ___\\__/___   " << endl;
        cout << "          | Stage 1: The Arena         (from Maze 01 to 10)         |     Beep.      __    |__|    |__|  " << endl;
        cout << "          | Stage 2: The Other Arena   (from Maze 11 to 20)         |               /__\\___/ /| [] | |   " << endl;
        cout << "          | Stage 3: Smiley            (from Maze 21 to 30)         |                __)____/ |    | |   " << endl;
        cout << "          | Stage 4: Heart             (from Maze 31 to 40)         |               \\__/      |____|_|   " << endl;
        cout << "          | Stage 5: Equivalent        (from Maze 41 to 50)         |                         | || |_/   " << endl;
        cout << "          | Stage 6: Fury              (from Maze 51 to 60)         |                         |_||_|     " << endl;
        cout << "           ---------------------------------------------------------                         _| || |_    " << endl;
        cout << "                                                                                            |___||___|   " << endl;
    }
    while (!success) {
        success = true;
        cout << setw(45) <<"\nPlease enter a maze number: ";
        cin >> n;
        if ( n < 0 || n > 99 || cin.fail()) {
            if (cin.eof()) {
                exit(0);
            }
            cout << "This is an invalid maze number!\nPlease bear in mind you can't use negative numbers nor one with more than two digits.\n";
            success = false;
        }
        else if (n > 60 && n < 100) {
            cout << "Actually, this game has only 60 mazes so please choose a smaller number.\nPfft, lazy developers.\n";
            success = false;
        }
    }

    if (n < 10 && n > 0) {
        str = "0" + to_string(n);
        return str;
    }
    return to_string(n);

}

void readHumanPlay(const vector<vector<char>> &maze, vector<int> &h) {
    cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| Q | W | E |" << endl;
    cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| A | S | D |" << endl;
    cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| Z | X | C |" << endl;
    cout << setw(60) << "-------------" << endl;

    char ch;
    int y, x;
    do {
        do {
            cout << "Enter key: ";
            cin >> ch;
            cin.ignore(10000, '\n');
            ch = toupper(ch);
            if ((ch != 'Q' && ch != 'W' && ch != 'E' && ch != 'A' && ch != 'S' && ch != 'D' && ch != 'Z' && ch != 'X' && ch != 'C' ) || cin.fail()) {
                if (cin.eof()) {
                    exit(0);
                }
                cin.clear();
                cin.ignore(100000, '\n');
                cout << "Invalid input!\n";
            }
            
        } while (ch != 'Q' && ch != 'W' && ch != 'E' && ch != 'A' && ch != 'S' && ch != 'D' && ch != 'Z' && ch != 'X' && ch != 'C' );
        
        y = h[0];
        x = h[1];
        switch (ch) {
            case 'Q':
                y--;
                x--;
                break;
            case 'W':
                y--;
                break;
            case 'E':
                y--;
                x++;
                break;
            case 'A':
                x--;
                break;
            case 'D':
                x++;
                break;
            case 'Z':
                y++;
                x--;
                break;
            case 'X':
                y++;
                break;
            case 'C':
                y++;
                x++;
                break;
            default:
                break;
        };

        if (maze[y][x] == 'r') {
            cout << "You can't move to a destroyed robot! Do you want to die?! " << endl;
        }
    } while (maze[y][x] == 'r');
    
    h[0] = y;
    h[1] = x;

}



void showMaze(const vector<vector<char>> &v) { 
    // prints out the maze
    cout << '\n';
    for (int i = 0; i < v.size(); i++) {
        cout << setw(35); 
        for (int j = 0; j < v[i].size(); j++) {
           cout << v[i][j] << ' '; 
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
    cout << "\n\n";
    cout << setw(45) <<"1) Rules "<< setw(15) << "2) Play " << setw(15) << "0) Exit\n\n";
    do {
        cout << "Enter option: ";
        cin >> x;
        if ((x != 0 && x != 1 && x != 2) || cin.fail()) {
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid input!\n";
        }
    } while (x != 0 && x != 1 && x != 2);
    return x;
}


void rules() {
    // prints rules
    cout << "\n           Here are the game's rules!" << endl;

    cout << "\n           Controls: " << endl;
    cout << "             \t-----------                          ----------------------------------- " << endl;
    cout << "            \t| Q | W | E |               :.       |  UP & LEFT  |  UP  |  UP & RIGHT  |" << endl;
    cout << "            \t-------------   :::::::::::::::.     -------------------------------------" << endl;
    cout << "            \t| A | S | D |   :::::::::::::::::.   |     LEFT    | STAY |     Right    |" << endl;
    cout << "            \t-------------   ::::::::::::::::'    -------------------------------------" << endl;
    cout << "            \t| Z | X | C |               ::'      | DOWN & LEFT | DOWN | DOWN & RIGHT |" << endl;
    cout << "             \t-----------                '         ----------------------------------- " << endl;


    cout << "\n          Your Objective:" << endl;
    cout << "           -------------------------------------------------------------------------------------" << endl;
    cout << "          | -> You have to destroy all the robots and survive their attack.                     |" << endl;
    cout << "          |                                                                                     |" << endl;
    cout << "          | -> To destroy them, you can navigate through the maze and try to bait the robots    |" << endl;
    cout << "          | into hitting a fence, a pole or another fellow robot. This way they will be unable  |" << endl;
    cout << "          | to pursue you.                                                                      |" << endl;
    cout << "          |                                                                                     |" << endl;
    cout << "          | -> However, you must be careful. Don't let the robots corner you. If they touch     |" << endl;
    cout << "          | you, they will capture you and it's game over. Also, you're not allowed to run into |" << endl;
    cout << "          | a destroyed robot, otherwise you'd die. Strategize your movements.                  |" << endl;
    cout << "           -------------------------------------------------------------------------------------" << endl;

    cout << "\n Press any key to continue." << endl;
    _getch();
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

vector<int> getHumanXY(const vector<vector<char>> &maze) {
    vector<int> v;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'H') {
                return {i, j};
            }
        }
    }
    return {-1};
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

    //check for robot collisions with fences and dead robots
    for (int i = 0; i < v.size(); i++) {
        if (maze[v[i][0]][v[i][1]] == '*' || maze[v[i][0]][v[i][1]] == 'r') {
            maze[v[i][0]][v[i][1]] = 'r';
            v.erase(v.begin() + i);
            i--;
        }
    }

    //check for robots collisions (robots with equal coordinates) and deletes them
    if (v.size() >= 2) {
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
    };
    // redraw human 
    if (maze[h[0]][h[1]] == '*' || maze[h[0]][h[1]]== 'r') {
        maze[h[0]][h[1]] = 'h';
    } else {
        maze[h[0]][h[1]] = 'H';
    }

    // redraw robots (think of joining with the loop below)
    for (int i = 0; i < v.size(); i++) {
        maze[v[i][0]][v[i][1]] = 'R';
    }

    //check if the human is alive
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == h) {
            maze[h[0]][h[1]] = 'h';
            break;
        }
    }

    

}

int checkGameOver(const vector<vector<char>> &maze) {
    // check whether there is an 'h' or if there are no 'R' -> GAME OVER
    // 0 - continue, 1 - robots win, 2 - hero/human wins
    int count = 0;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'h') {
                return 1;
            }
            if (maze[i][j] == 'R') {
                count++;
            }
        }
    }
    if (count == 0) {
        return 2;
    }
    return 0;

}

struct Player {
    string name;
    int time;
};

string strip(string str) {
    // removes the leading and trailing whitespaces of a string
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return str.substr(start, end-start+1);
}

string fill15(string name) {
    while (name.length() < 15) {
        name += ' ';
    }
    return name; 
}

string readName() {
    // reads the name of the player, but it can only have 15 characters!!!
    // if smaller, fills the name with whitespace
    string name;
    do {
        cout << "Enter your name: ";
        cin >> name;
        if ( name.length() > 15 || cin.fail()) {
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid input!\n";
        }
    } while (name.length() > 15);

    return fill15(name);  
}

void bubbleSort(vector<Player> &v) {
    // sorting function to sort the times of the winners
    Player aux;
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < v.size()-1; i++) {
            if (v[i].time > v[i+1].time ) {
                change = true;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
    }
}

void gameOver(int x, int time, string filename) {
    // check if it won, and if so
    // ask the name
    // sort the winning times
    if (x == 2) {
        cout << "Congratulations, you won!!!" << endl;

        ifstream file;
        file.open(filename);
        if (!file.is_open()) {
            cout << "File not found" << endl;
        } else {
            vector<Player> v = {};
            Player p;
            string line;
            size_t pos;

            p.name = readName();
            p.time = time;
            v.push_back(p);

            ofstream temp;
            temp.open("temp.txt");

            getline(file, line);    // ignore the first 2 lines of the file
            temp << line << endl;   // Lines: (Player - Time) and (---------)     we can put it in a cycle, but there's only 2...
            getline(file, line);    
            temp << line << endl;   
            while (getline(file, line)) {
                pos = line.find('-') + 1;
                p.time = stoi(strip(line.substr(pos)));
                p.name = fill15(strip(line.substr(0, 15)));
                v.push_back(p);
            }
            bubbleSort(v);
            
            cout << "\nNew times: " << endl;
            for(int i = 0; i < v.size(); i++) {
                temp << v[i].name << "  - " << v[i].time << endl;
                cout << v[i].name << "  - " << v[i].time << endl;
            }
            temp.close();
            file.close();
            const char* filename_c = filename.c_str();
            remove(filename_c);
            rename("temp.txt", filename_c);
            cout << "\nI hope you have enjoyed our game!";
        }
    } else {
        cout << "Game Over!" << endl;
        cout << "You Lost" << endl;
    }
}
