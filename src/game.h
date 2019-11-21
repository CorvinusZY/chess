//
//  game.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef game_h
#define game_h
#include <iostream>
#include <string>
#include <vector>
#include "basicpiece.h"
#include "king.h"
#include "display.h"
#include "biship.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "computer.h"
#include "step.h"
#include "basicpiece.h"
using namespace std;
/*
class rook;
class knight;
class king;
class queen;
class pawn;
class biship;
class display;
class computer;
*/
class game {
    display* mydisplay;
    vector<vector<basicpiece *>> board{};
    computer *AI1;
    computer *AI2;
    
    
    
    vector<int> initial_time{};
    vector<vector<int>>pawn_initial2{};
    //int initial_time = -1;
    //vector<int> pawn_initial2{};
    
    Color currplayer;
public:
    bool humanVH;
    bool humanVC;
    bool computerVC;
    bool initialized = false;
    bool issetup = false;
    
    void displayboard();
    void promoteP(vector<int> origin, vector<int> target, string promote);
    game(const game &other);
    game(bool humanVH = false, bool humanVC = false, bool computerVC = false, int level1=0, int level2=0, Color currplayer = Color::black);
    ~game();
    void initial(); //game should be initialized after setup mode(if setup mode is entered)
    void entersetup();//denotes the game with setup board
    void setup(vector<int>target);//deletes a piece in a specific spot
    void setup(vector<int>target, Piece type, Color player); //places a piece in a specific spot
    Color whoWon();
    bool isWon();
    void move(vector<int> origin, vector<int> target, Color player);
    bool blackisCheck();
    bool whiteisCheck();
    bool blackisCheckmate();
    bool whiteisCheckmate();
    bool isStalemate();
    basicpiece *getpiece(vector<int> dest);
    basicpiece *gettype(Color player, Piece type);
    vector<step> blackvalids();
    vector<step> whitevalids();
    Color getcurr();
    void setplayer(Color curr);
    void addComputer(int num, int diff);
    step AIMove(int ainum);
    bool setupdone();
    
    friend class basicpiece;
    friend class king;
    friend class biship;
    friend class queen;
    friend class rook;
    friend class knight;
    friend class pawn;
    friend class computer;
    friend class display;
    //helpers
    friend void findline_nocheck(vector<step> &valids, step currentline, int y, int x, game *mygame);
    friend bool checkstep_nocheck (step target, game *mygame);
    friend bool inrange(vector<int> target);
    //used to check whether a coordinate is in the board
    friend void findline(vector<step> &valids, step currentline, int y, int x, game *mygame);
    //used to find all valid moves for a given piece that moves in a straight line
    //the function should only be used for biships, queens, and rooks
    friend bool checkstep (step target, game *mygame);
    //checkstep() simply checks whether target piece is empty or obtainable and whether
    //target is in range
    

};

//helpers

bool inrange(vector<int> target);
//used to check whether a coordinate is in the board
void findline(vector<step> &valids, step currentline, int y, int x, game *mygame);
//used to find all valid moves for a given piece that moves in a straight line
//the function should only be used for biships, queens, and rooks
bool checkstep (step target, game *mygame);
//checkstep() simply checks whether target piece is empty or obtainable and whether
//target is in range

#endif /* game_hpp */
