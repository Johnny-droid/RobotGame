#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Position {
 int row, col;
};
 
class Menu {
    public: 
        Menu(int menuCtrl);
        string readMazeNumber();
        void showTitle() const;


    private:
        int _menuCtrl;
};

class Player {
    public:
        Player(int row, int col, char symbol);
        Player();
        int getRow() const;
        int getCol() const;
        int getMovCol() const;
        int getMovRow() const;
        Position getMovement() const;
        Position getPosition() const;
        char getSymbol() const;
        bool isAlive() const;
        void setAsDead();
        void setMovement(Position & movement);
        void updateMovement();
        void show() const;
    private:
        Position _position, _movement;
        char _symbol;
};

class Robot {
    public:
        Robot(int row, int col, int id);
        int getID() const;
        char getSymbol() const; // get char representation of robot (R if alive, r if dead)
        int getRow() const;
        int getCol() const;
        int getMovRow() const;
        int getMovCol() const;
        Position getPosition() const;
        Position getMovement() const;
        bool isAlive() const;
        void setRow(int x);
        void setCol(int y);
        void setPosition(const Position &pos);
        void setMovement(const Position &mov);
        void updateMovement();
        void setAsDead();
        void show() const;
    //other methods
    private:
        // static int _robotCounter; //used to attribute automatically the id to the robots
        int _id;
        Position _position, _movement;
        bool _alive;
    // other attributes (?)
};

class Post {
    public:
        Post(int row, int col, char type, bool destroyed = false);
        int getRow() const;
        int getCol() const;
        Position getPosition() const;
        char getSymbol() const; // get char representation of Post
        bool isElectrified() const;
        bool isDestroyed();
        void setPosition(const Position &pos);
        void setDestroyed();
        void show() const;
 //other methods
    private:
        Position _position;
        bool _destroyed;
        char _type; // '*' - electrified; '+'- non-electrified
        // other attributes (?)
};

class Maze {
    public:
        Maze(int numRows, int numCols, vector<Position> gates, vector<Post> posts);
        Maze();
        void addPost(const Post& post);
        int getnumRows() const;
        int getnumCols() const;
        vector<Position> getGates() const;
        vector<Post> getPosts() const;
        void show() const;
        // other methods
    private:
        int _numRows, _numCols;
        vector<Position> _gates;
        vector<Post> _posts;
        // data structure that represents the posts
};

class Game {
    public:
        Game(const string & filename);
        bool play(); // implements the game loop; returns true if player wins, false otherwise
        bool isValid();
    
    private:
        void showGameDisplay() const;
        bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
        bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
        bool collide(Post& post, Player& player); //check if human collided with post
        void readHumanPlay();
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