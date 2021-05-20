#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "MazeClasses.hpp"
using namespace std;


// Player

Player::Player(int row, int col, char symbol) {
	_row = row;
	_col = col;
	_symbol = symbol;
}

Player::Player() {
	_row = 0;
	_col = 0;
	_symbol = 'h';
}

int Player::getCol() const {
	return _col;
}

int Player::getRow() const {
	return _row;
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

void Player::show() const {
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Alive: " << isAlive() << endl;
}

void Player::setAsDead() {
	_symbol = 'h';
}

// Robot

Robot::Robot(int row, int col) {
	_row = row;
	_col = col;
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
	return _row;
}

int Robot::getCol() const {
	return _col;
}

bool Robot::isAlive() const {
	return _alive;
}



/*
Position Robot::getPosition() const {}
void Robot::setPosition(const Position &pos) {}
*/

void Robot::setRow(int x) {
	_row = x;
}

void Robot::setCol(int y) {
	_col = y;
}

void Robot::setAsDead() {
	_alive = false;
}

void Robot::show() const {
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Number of ID: " << getID() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Alive: " << isAlive() << endl;
}

// Post

Post::Post(int row, int col, char type) {
	_row = row;
	_col = col;
	_type = type;
}

int Post::getRow() const {
	return _row;
}

int Post::getCol() const {
	return _col;
}

char Post::getSymbol() const {
	return _type;
}

bool Post::isElectrified() const {
	if (_type == '*') {
		return true;
	}
	return false;
}

void Post::setPosition(const Position &pos) {
	_row = pos.row;
	_col = pos.col;
}

void Post::show() const {
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

void Maze::show() const {
	vector<vector<char>> maze = {};
	vector<char> v = {};
	
	for (size_t i = 0; i < _numRows; i++) {
		
	}
	
	for (Post p : _posts) {
		maze[p.getRow()][p.getCol()] = p.getSymbol();
	}

	// add gate
	for (Position gate : _gates) {
		maze[gate.row][gate.col] = 'O';
	}
	

	for (int i = 0; i < _numRows; i++) {
		for (int j = 0; j < _numRows; j++) {
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
    }
	else {
		vector<Post> posts = {};
		vector<Robot> robots = {};
		vector<Position> gates = {};
		Player player;
		string line;
		int i = 0, nrow, ncol;

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
					Robot rbt(i, j);
					robots.push_back(rbt);
				} else if (line[j] == 'H') {
					Player player(i, j, 'h'); 
				} else if (line[j] == 'O') {
					Position gate = {i, j};
					gates.push_back(gate);
				}
			};
			i++;
		};
		file.close();
		
		Maze maze(nrow, ncol, gates, posts);
		_maze = maze;
		_robots = robots;
		_player = player;

	}
};

/*
    public:
        Game(const string & filename);
        // This constructor should initialize the Maze, the vector of Robots, and the Player,
        // using the chars read from the file
        bool play(); // implements the game loop; returns true if player wins, false otherwise
        bool isValid();
    
    private:
        void showGameDisplay() const;
        bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
        bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
        // other methods, for example:
        // to check if player is trying to move to a valid place
        // to apply a valid play and check collisions
        // to check if two robots collide (and possibly set them as dead)
        // etc.
    private:
        Maze _maze;
        Player _player;
        vector<Robot> _robots;
        //other attributes
*/
