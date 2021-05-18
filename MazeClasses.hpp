#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Movement {
 int dRow, dCol; // displacement, taking into account the chosen movement
};

struct Position {
 int row, col;
};
 

class Player {
    public:
        Player(int row, int col, char symbol);
        int getRow() const;
        int getCol() const;
        char getSymbol() const;
        bool isAlive() const;
        void setAsDead();
        bool move(Movement delta);
        void show() const;
    private:
        int _row, _col;
        bool _alive;
        char _symbol;
};

class Robot {
    public:
        enum State { ALIVE, STUCK, DEAD };
        Robot(int row, int col);
        int getID() const;
        char getSymbol() const; // get char representation of robot (R if alive, r if dead)
        int getRow() const;
        int getCol() const;
        Position getPosition() const;
        bool isAlive() const;
        void setRow(int x);
        void setCol(int y);
        void setPosition(const Position &pos);
        void setAsDead();
        void show() const;
    //other methods
    private:
        static int _robotCounter; //used to attribute automatically the id to the robots
        int _id;
        int _row, _col;
        bool _alive;
    // other attributes (?)
};

class Post {
    public:
        Post(int row, int col, char type);
        int getRow() const;
        int getCol() const;
        char getSymbol() const; // get char representation of Post
        bool isElectrified() const;
        void setPosition(const Position &pos);
        void show() const;
 //other methods
    private:
        int _row, _col;
        char _type; // '*' - electrified; '+'- non-electrified
        // other attributes (?)
        // could also have a state, like the robot(?)
};

class Maze {
    public:
        Maze(int numRows, int numCols);
        void addPost(const Post& post);
        int getnumRows() const;
        int getnumCols() const;
        void show() const;
        // other methods
    private:
        int _numRows, _numCols;
        int coord_x_gate, coord_y_gate;
        vector<Post> posts;
        // data structure that represents the posts
};

class Game {
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
};

/*
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
*/