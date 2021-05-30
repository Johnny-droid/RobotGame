#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Struct used to indicate the position of multiple objects (ex: Player, Robots, Posts)
// and also their movement in the case of Player and Robots (since Posts don't move)
struct Position {
 int row, col;
};

// Struct used to save and sort the times of the winners in the files. It isn't related to the game itself
struct PlayerTable {
    string name;
    int time;
};

// functions used mainly to handle things unrelated to the game itself (ex: menu, rules, winners, etc...)
void showTitle();           // shows the Main Menu
int selectOption();         // reads the option in the Main Menu
void printRules();          // prints the rules from the file RULES.txt
void printLeaderBoard(string winnersFile);    // prints the Leaderboard of the file "winnersFile"
string readMazeNumber();                      // returns the maze number as a string ex: 01 or 24
string readLeaderboardNumber();               // return the number in the same format as readMazeNumber()
void gameOver(int x, int time, string filename);   // Ending of the game. it also shows and records your time if you won.
bool replay();                                  // Asks the player if he wants to continue to play or exit the game

// auxiliary functions
string strip(string str);
string fill15(string name);  //fill the string until it has 15 spaces
string readName();           // reads the name for the winners table
void bubbleSort(vector<PlayerTable> &v);

// Operators for positions
Position operator+(Position pos1, Position pos2);
bool operator==(Position pos1, Position pos2);

//===========CLASSES==============
//Player
//Robot
//Post
//Maze
//Game


class Player {
    // It's the class Player. The objective is for it to reach one of the gates in the maze
    // _position -> current position            _movement -> diretion in which it will move
    //                    future position = _position + _movement
    // _symbol = 'H' if the player is still alive and 'h' if the player is dead
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
        void setMovementZero();   // _movement is set to {0, 0}
        void updateMovement();    // the player advances (_position = _position + _movement)
        void show() const;        // used for development only. It displays the atributes of the player
    private:
        Position _position, _movement;
        char _symbol;
};

class Robot {
    // It's the class Robot. The objective is for it to reach the player and kill it
    // the positions work the same way as the player and here, instead of a symbol, a boolean atribute represents if he is either destroyed (dead) or alive
    // all robots have a unique id (starting at 1 and ending in the total number of robots)
    public:
        Robot(int row, int col, int id, bool alive = true);
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
        void setMovementZero();
        void updateMovement();
        void setAsDead();
        void show() const;    //used for development

    private:
        int _id;
        Position _position, _movement;
        bool _alive;
};

class Post {
    // It's the class Post. It does basically nothing. It only gets in the way of players and robots
    // the are two types of posts    + -> non-eletric            * -> eletric
    // the atribute destroyed is only used in non-eletric Posts, when a robot lands on it and destroys it.
    public:
        Post(int row, int col, char type, bool destroyed = false);
        int getRow() const;
        int getCol() const;
        Position getPosition() const;
        char getSymbol() const;            // get char representation of Post
        bool isElectrified() const;
        bool isDestroyed();
        void setPosition(const Position &pos);
        void setDestroyed();
        void show() const;    // used for development

    private:
        Position _position;
        bool _destroyed;
        char _type; // '*' - electrified; '+'- non-electrified
};

class Maze {
    // It's the class Maze. It's basically the map where you will be playing. It has both the posts and gates
    public:
        Maze(int numRows, int numCols, vector<Position> gates, vector<Post> posts);
        Maze();
        void addPost(const Post& post);
        int getnumRows() const;
        int getnumCols() const;
        vector<Position> getGates() const;
        vector<Post> &getPostsByRef();   // used when it's necessary to alter the posts
        vector<Post> getPosts() const;  
        void show() const;              // used for development
    private:
        int _numRows, _numCols;
        vector<Position> _gates;
        vector<Post> _posts;
};

class Game {
    // It's the class Game. It coordinates the interaction between all things (Players, Robots and the Maze)
    // The valid atribute is just to check if there was any problem 
    public:
        Game(const string & filename);   // builds the game with the name of the file
        bool isValid();
        void readHumanPlay();            // asks the player for its move and checks if it's valid
        void updateRobots();             // calculates the movement of the robots according to the position of the player
        void updateGame();               // updates the Game. updates the postions of the robots according to the interation with other elements
        void showGameDisplay() const;    // simply shows the game
        int checkGameOver();             // checks if the game has already ended and if so, who won. (// 0 -> continue,    1 -> robots win,   2 -> hero/human wins)
        
    private:
        bool collide(Robot& robot, Post& post);     // check if robot collided with post 
        bool collide(Robot& robot, Player& player); // check if human and robot collided
        bool collide(Post& post, Player& player);   // check if human collided with post
        
    private:
        Maze _maze;
        Player _player;
        vector<Robot> _robots;
        bool _valid;
};
