#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "MazeClasses.hpp"
using namespace std;


// Player

Player::Player(int row, int col, char symbol) {
	_position = {row, col};
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

Robot::Robot(int row, int col, int id) {
	_position = {row, col};
	_id = id;
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

/*
Position Robot::getPosition() const {}

*/

void Robot::setRow(int x) {
	_position.row = x;
}

void Robot::setCol(int y) {
	_position.col = y;
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
	_position = {row, col};
	_type = type;
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

bool Post::isElectrified() const {
	if (_type == '*') {
		return true;
	}
	return false;
}

void Post::setPosition(const Position &pos) {
	_position = pos;
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
    }
	else {
		vector<Post> posts = {};
		vector<Robot> robots = {};
		vector<Position> gates = {};
		Player player;
		string line;
		int nRobot = 1;
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
					Robot rbt(i, j, nRobot);
					nRobot++;
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

bool Game::collide(Robot& robot, Post& post) {
	Position future_pos = {robot.getRow() + robot.getMovRow() , robot.getCol() + robot.getMovCol() };
	if (future_pos.row == post.getRow && future_pos.col == post.getCol()) {
		if (post.isElectrified()) {
			
		}
	}
}

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
