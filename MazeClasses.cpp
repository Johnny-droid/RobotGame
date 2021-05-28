#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "MazeClasses.hpp"
using namespace std;

Position operator+(Position pos1, Position pos2) {
	return {pos1.row + pos2.row, pos1.col + pos2.col };
}

bool operator==(Position pos1, Position pos2) {
	if (pos1.row == pos2.row && pos1.col == pos2.col) {
		return true;
	}
	return false;
}

// Menu

 void Menu::showTitle() const {
	cout << "\n\n";
    cout << "\t\t\t _____   ____  ____   ____ _______  __          __     _____   _____" << endl;
    cout << "\t\t\t|  __ \\ / __ \\|  _ \\ / __ \\__   __| \\ \\        / /\\   |  __ \\ / ____|" << endl;
    cout << "\t\t\t| |__) | |  | | |_) | |  | | | |     \\ \\  /\\  / /  \\  | |__) | (___" << endl;
    cout << "\t\t\t|  _  /| |  | |  _ <| |  | | | |      \\ \\/  \\/ / /\\ \\ |  _  / \\___ \\ " << endl;
    cout << "\t\t\t| | \\ \\| |__| | |_) | |__| | | |       \\  /\\  / ____ \\| | \\ \\ ____) |" << endl;
    cout << "\t\t\t|_|  \\_\\\\____/|____/ \\____/  |_|        \\/  \\/_/    \\_\\_|  \\_\\_____/ " << endl;
    cout << endl;
}

string Menu::readMazeNumber() {
	int n;
    string str;
    bool success = false;

	cout << setw(45) << "--------------------------------------------------" << endl;
	cout << setw(45) << "| These are the mazes you can play in. Have fun! |" << endl;
	cout << setw(45) << "--------------------------------------------------\n" << endl;
	cout << setw(45) << "Maze 01: The Arena  " << endl;
	cout << setw(45) << "**************************     There are more       _\\/_   " << endl;
	cout << setw(45) << "*                        *     robots like me      [____]  " << endl;
	cout << setw(45) << "*     *  ++++++++  *     *     on the later mazes. |()()|" << endl;
	cout << setw(45) << "*                        *     Choose wisely.    ___\\__/___  " << endl;
	cout << setw(45) << "*     +            +     *     Beep.      __    |__|    |__| " << endl;
	cout << setw(45) << "*     +     **     +     *               /__\\___/ /| [] | |" << endl;
	cout << setw(45) << "*     +     **     +     *                __)____/ |    | | " << endl;
	cout << setw(45) << "O     +            +     O               \\__/      |____|_|" << endl;
	cout << setw(45) << "*                        *                         | || |_/" << endl;
	cout << setw(45) << "*     *  ++++++++  *     *                         |_||_| " << endl;
	cout << setw(45) << "*                        *                        _| || |_ " << endl;
	cout << setw(45) << "***********O**O***********                       |___||___|\n" << endl;
	cout << setw(45) << "Maze 02: The Angry Face          Maze 03: The Cat" << endl;
	cout << setw(45) << "*****************************    ****O*O*O**************O*O*O****" << endl;
	cout << setw(45) << "*                           *    *                              *" << endl;
	cout << setw(45) << "*       +           +       *    *    +++                +++    *" << endl;
	cout << setw(45) << "*         +       +         *    *    +   +            +   +    *" << endl;
	cout << setw(45) << "*         * +   + *         *    *    +    +          +    +    *" << endl;
	cout << setw(45) << "*         *       *         *    *                              *" << endl;
	cout << setw(45) << "*         *       *         *    *            *    *            *" << endl;
	cout << setw(45) << "*         *       *         *    *            *    *            *" << endl;
	cout << setw(45) << "*             *             *    *                              *" << endl;
	cout << setw(45) << "*                           *    *     +++              +++     *" << endl;
	cout << setw(45) << "*          +++++++          *    *            *    *            *" << endl;
	cout << setw(45) << "*        ++       ++        *    *             ****             *" << endl;
	cout << setw(45) << "*                           *    *                              *" << endl;
	cout << setw(45) << "****O****O****O****O****O****    ********************************" << endl;


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
            cout << "Actually, this game has only 3 mazes so please choose a smaller number.\nPfft, lazy developers.\n";
            success = false;
        }
    }

    if (n < 10 && n > 0) {
        str = "0" + to_string(n);
        return str;
    }
    return to_string(n);
}



string Menu::strip(string str) {
    // removes the leading and trailing whitespaces of a string
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return str.substr(start, end-start+1);
};

string Menu::fill15(string name) {
    while (name.length() < 15) {
        name += ' ';
    }
    return name; 
};

string Menu::readName() {
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

void Menu::bubbleSort(vector<PlayerTable> &v) {
    // sorting function to sort the times of the winners
    PlayerTable aux;
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

void Menu::gameOver(int x, int time, string filename) {
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
            vector<PlayerTable> v = {};
            PlayerTable p;
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
// Player

Player::Player(int row, int col, char symbol) {
	Position pos =  {row, col};
	_position = pos;
	_symbol = symbol;
}

Player::Player() {
	_position = {0, 0};
	_symbol = 'h';
}

int Player::getCol() const {
	return _position.col;
}

int Player::getRow() const {
	return _position.row;
}

int Player::getMovCol() const {
	return _movement.col;
}

int Player::getMovRow() const {
	return _movement.row;
}

Position Player::getPosition() const {
	return _position;
}

Position Player::getMovement() const {
	return _movement;
}

char Player::getSymbol() const {
	return _symbol;
}

bool Player::isAlive() const {
	if (_symbol == 'H') {
		return true;
	}
	return false;
}

void Player::show() const {                                        //show, just for testing
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Alive: " << isAlive() << endl;
}

void Player::setAsDead() {
	_symbol = 'h';
}

void Player::setMovement(Position & movement) {
	_movement = movement;
}

void Player::setMovementZero() {
	Position movement = {0, 0};
	_movement = movement;
}

void Player::updateMovement() {
	_position = {_position.row + _movement.row, _position.col + _movement.col};
	_movement = {0, 0};
}

// Robot

Robot::Robot(int row, int col, int id, bool alive) {
	_position = {row, col};
	_id = id;
	_alive = alive;
}

int Robot::getID() const {
	return _id;
}

char Robot::getSymbol() const {
	if (_alive) {
		return 'R';
	}
	return 'r';
}

int Robot::getRow() const {
	return _position.row;
}

int Robot::getCol() const {
	return _position.col;
}

int Robot::getMovRow() const {
	return _movement.row;
}

int Robot::getMovCol() const {
	return _movement.col;
}

bool Robot::isAlive() const {
	return _alive;
}

void Robot::setPosition(const Position &pos) {
	_position = pos;
}

void Robot::setMovement(const Position &mov) {
	_movement = mov;
}

void Robot::setMovementZero() {
	Position movement = {0, 0};
	_movement = movement;
}

void Robot::updateMovement() {
	_position = _position + _movement;
	_movement = {0, 0};
}

Position Robot::getPosition() const {
	return _position;
}

Position Robot::getMovement() const {
	return _movement;
}

void Robot::setRow(int x) {
	_position.row = x;
}

void Robot::setCol(int y) {
	_position.col = y;
}

void Robot::setAsDead() {
	_alive = false;
}

void Robot::show() const {                                    //show, just for testing
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Number of ID: " << getID() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Alive: " << isAlive() << endl;
}


// Post

Post::Post(int row, int col, char type, bool destroyed /*=false*/) {
	_position = {row, col};
	_type = type;
	_destroyed = destroyed;
}

int Post::getRow() const {
	return _position.row;
}

int Post::getCol() const {
	return _position.col;
}

char Post::getSymbol() const {
	return _type;
}

Position Post::getPosition() const {
	return _position;
}

bool Post::isElectrified() const {
	if (_type == '*') {
		return true;
	}
	return false;
}

bool Post::isDestroyed() {
	return _destroyed;
}


void Post::setPosition(const Position &pos) {
	_position = pos;
}

void Post::setDestroyed() {
	_destroyed = true;
}

void Post::show() const {                                 //show, just for testing
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Electrified: " << isElectrified() << endl;
}

// Maze

Maze::Maze(int numRows, int numCols, vector<Position> gates, vector<Post> posts) {
	_numRows = numRows;
	_numCols = numCols;
	_posts = posts;
	_gates = gates;
};

Maze::Maze() {
	_numRows = 0;
	_numCols = 0;
	_gates = {};
	_posts = {};
}

void Maze::addPost(const Post& post) {
	_posts.push_back(post);
};

int Maze::getnumCols() const {
	return _numCols;
};

int Maze::getnumRows() const {
	return _numRows;
};

vector<Position> Maze::getGates() const {
	return _gates;
}

vector<Post> Maze::getPosts() const {
	return _posts;
}

void Maze::show() const {
	vector<vector<char>> maze = {};
	vector<char> v;
	
	for (size_t i = 0; i < _numRows; i++) {
		v = {};
		for (size_t j = 0; j < _numCols; j++) {
			v.push_back(' ');
		}
		maze.push_back(v);
	}
	
	for (Post p : _posts) {
		maze[p.getRow()][p.getCol()] = p.getSymbol();
	}

	// add gate
	for (Position gate : _gates) {
		maze[gate.row][gate.col] = 'O';
	}
	
	// print
	for (int i = 0; i < _numRows; i++) {
		for (int j = 0; j < _numCols; j++) {
			cout << maze[i][j] << ' ';
		}
		cout << endl;
	}
};

// Game

Game::Game(const string & filename) {
	ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Maze not found!" << endl;
    } else {
		vector<Post> posts = {};
		vector<Robot> robots = {};
		vector<Position> gates = {};
		string line;
		int nRobot = 1;
		int i = 0, nrow, ncol, row, col;

		// get number of rows and cols
		getline(file, line);
		int x = line.find('x');
		nrow = stoi(line.substr(0, x));
		ncol = stoi(line.substr(x+1));

		while (getline(file, line)) {
			for (int j = 0; j < line.size(); j++) {
				if ( line[j] == '*' || line[j] == '+') {
					Post pst(i, j, line[j]);
					posts.push_back(pst);
				} else if ( line[j] == 'R') {
					Robot rbt(i, j, nRobot);
					nRobot++;
					robots.push_back(rbt);
				} else if (line[j] == 'H') {
					row = i;
					col = j;
				} else if (line[j] == 'O') {
					Position gate = {i, j};
					gates.push_back(gate);
				}
			};
			i++;
		};
		file.close();
		
		Player pl(row, col, 'H');
		Maze maze(nrow, ncol, gates, posts);
		_maze = maze;
		_robots = robots;
		_player = pl;

	}
};

bool Game::collide(Robot& robot, Post& post) {
	if (robot.getPosition() + robot.getMovement() == post.getPosition()) {
		robot.setAsDead();
		if (!post.isElectrified()) {
			robot.updateMovement();
			post.setDestroyed();
		}
		return true;
	}
	return false;
}

bool Game::collide(Robot& robot, Player& player) {
	if ( (robot.getPosition() + robot.getMovement()) == (player.getMovement() + player.getPosition()) ) {
		return true;
	}
	return false;
}

bool Game::collide(Post& post, Player& player) {
	if (player.getPosition() + player.getMovement() == post.getPosition()) {
		return true;
	}
	return false;
}

void Game::showGameDisplay() const {
	vector<vector<char>> mazeDisplay = {};
	vector<char> v;
	
	for (size_t i = 0; i < _maze.getnumRows(); i++) {
		v = {};
		for (size_t j = 0; j < _maze.getnumCols(); j++) {
			v.push_back(' ');
		}
		mazeDisplay.push_back(v);
	}
	
	//posts
	for (Post p : _maze.getPosts()) {
		mazeDisplay[p.getRow()][p.getCol()] = p.getSymbol();
	}

	//gates
	for (Position gate : _maze.getGates()) {
		mazeDisplay[gate.row][gate.col] = 'O';
	}
	
	//robots
	for (Robot r : _robots) {
		mazeDisplay[r.getRow()][r.getCol()] = r.getSymbol();
	}

	//player
	mazeDisplay[_player.getRow()][_player.getCol()] = _player.getSymbol();

	// print
	for (int i = 0; i < _maze.getnumRows(); i++) {
		for (int j = 0; j < _maze.getnumCols(); j++) {
			cout << mazeDisplay[i][j] << ' ';
		}
		cout << endl;
	}
}

void Game::readHumanPlay() {
	cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| Q | W | E |" << endl;
    cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| A | S | D |" << endl;
    cout << setw(60) << "-------------" << endl;
    cout << setw(60) << "| Z | X | C |" << endl;
    cout << setw(60) << "-------------" << endl;

    char ch;
	bool validPos;
	Position mov;
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

        switch (ch) {
            case 'Q':
				mov = {-1, -1};
                break;
            case 'W':
				mov = {-1, 0};
                break;
            case 'E':
				mov = {-1, 1};
                break;
            case 'A':
				mov = {0, -1};
                break;
            case 'D':
				mov = {0, 1};
                break;
            case 'Z':
				mov = {1, -1};
                break;
            case 'X':
				mov = {1, 0};
                break;
            case 'C':
				mov = {1, 1};
                break;
            default:
				mov = {0, 0};
                break;
        };
		_player.setMovement(mov);
		validPos = true;
		for (Robot r: _robots) {
			if (!r.isAlive() && collide(r, _player)) {
				validPos = false;
				break;
			}
		}

		for (Post p: _maze.getPosts()) {
			if (!p.isElectrified() && collide(p, _player)) {
				validPos = false;
				break;
			}
		}
        
    } while (!validPos);
    _player.updateMovement();
}

void Game::updateRobots() {
	Position mov;
	for (Robot r : _robots) {
        if (!r.isAlive()) {
			continue;
		}
		if (r.getCol() == _player.getCol() && r.getRow() < _player.getRow()) {
			mov = {1, 0};
        } else if (r.getCol() == _player.getCol() && r.getRow() > _player.getRow()) {
            mov = {-1, 0};
        } else if (r.getRow() == _player.getRow() && r.getCol() < _player.getCol()) {
            mov = {0, 1};
        } else if (r.getRow() == _player.getRow() && r.getCol() > _player.getCol()) {
            mov = {0, -1};
        } else if (r.getCol() < _player.getCol() && r.getRow() < _player.getRow()) {
            mov = {1, 1};
        } else if (r.getCol() < _player.getCol() && r.getRow() > _player.getRow()) {
            mov = {-1, 1};
        } else if (r.getCol() > _player.getCol() && r.getRow() < _player.getRow()) {
            mov = {1, -1};
        } else if (r.getCol() > _player.getCol() && r.getRow() > _player.getRow()) {
            mov = {-1, -1};
        }
		r.setMovement(mov);
		r.updateMovement();   //not sure
    }
}

void Game::updateGame() {
    //check for robot collisions with fences
	for (Robot r: _robots) {
		if (!r.isAlive()) {
			continue;
		}
		for (Post p: _maze.getPosts()) {
			if (r.getPosition() + r.getMovement() == p.getPosition()) {
				r.setAsDead();
				if (!p.isElectrified()) {
					r.updateMovement();
				} else {
					r.setMovementZero();
				}
			}
		}
	}

	//check for robot collisions with each other
	for (size_t i = 0; i < _robots.size()-1; i++) {
		for (size_t j = i+1; j < _robots.size(); j++) {
			Robot& r1 = _robots[i];
			Robot& r2 = _robots[j];
			if (r1.getPosition() + r1.getMovement() == r2.getPosition() + r2.getMovement()) {
				r1.updateMovement();
				r2.updateMovement();
				r1.setAsDead();
				r2.setAsDead();
			} 
		}
	}

	//checks if human is still alive 
	for (Post p: _maze.getPosts()) {
		if (collide(p, _player)) {
			_player.setAsDead();
			_player.setMovementZero();
			break;
		}
	}

	for (Robot r: _robots) {
		if (collide(r, _player)) {
			_player.setAsDead();
			_player.setMovementZero();
			break;
		}
	}

	//updates robots positions
	for (Robot r: _robots) {
		r.updateMovement();
	}
}

// 0 - continue, 1 - robots win, 2 - hero/human wins
int Game::checkGameOver() {
	if (!_player.isAlive()) {
		return 1;
	}
	for (Position gate : _maze.getGates()) {
		if (gate == _player.getPosition() ) {
			return 2;
		}
	}
	return 0;
} 

