#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Post {
    private:
		bool eletric;
		int coord_x;
		int coord_y;
};

class Robot {
	private:
		bool alive;
		int coord_x;
		int coord_y;

};

class Player {
    private:
		bool alive;
		int coord_x;
		int coord_y;

};

class Maze {
	private:
		int dim_x;
		int dim_y;
		int coord_x_gate;
		int coord_y_gate;
		vector<Post> posts;

};

class Game {
	private:
		int time;
		Maze maze;
		Player player;
		vector<Robot> robots;

};
