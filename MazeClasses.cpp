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
	return _alive;
}

void Player::show() const {
	cout << "Number of row: " << getRow() << endl;
	cout << "Number of col: " << getCol() << endl;
	cout << "Symbol: " << getSymbol() << endl;
	cout << "Alive: " << isAlive() << endl;
}

void Player::setAsDead() {
	_alive = false;
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

Maze::Maze(int numRows, int numCols) {
	_numRows = numRows;
	_numCols = numCols;
};

void Maze::addPost(const Post& post) {
	posts.push_back(post);
};

int Maze::getnumCols() const {
	return _numCols;
}

int Maze::getnumRows() const {
	return _numRows;
};

void Maze::show() const {
	vector<vector<char>> maze = {};
	vector<char> v = {};
	// first row
	for (int j = 0; j < _numCols; j++) {
		v.push_back('*');
	};
	maze.push_back(v);
	v = {};

	// middle rows
	for (int i = 0; i < _numRows - 1; i++) {
		v.push_back('*');
		for (int j = 1; j < _numCols-1; j++) {
			v.push_back(' ');
		}
		v.push_back('*');
		maze.push_back(v);
		v = {};
	}

	// final row
	for (int j = 0; j < _numCols; j++) {
		v.push_back('*');
	};
	maze.push_back(v);

	// add posts
	for (Post p : posts) {
		maze[p.getRow()][p.getCol()] = p.getSymbol();
	}

	// add gate
	maze[coord_y_gate][coord_x_gate] = 'O';

	for (int i = 0; i < _numRows; i++) {
		for (int j = 0; j < _numRows; j++) {
			cout << maze[i][j] << ' ';
		}
		cout << endl;
	}
}


