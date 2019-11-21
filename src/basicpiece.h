//
//  basicpiece.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef basicpiece_h
#define basicpiece_h

#include <vector>
using namespace std;

enum class Piece {K, Q, B, R, KN, P};
enum class Color {black, white};
class game;
class step;

class basicpiece {
protected:
    vector<int> position;
    Piece type;
    Color player;
    game *mygame;
public:
    
    void setgame(game *thegame);
    virtual basicpiece *duplicate() = 0;
    virtual void initialize(int moves);
    virtual bool isinitial();
    virtual void deinitial2();
    virtual bool justinitial2();
    Color getcolor();
    Piece getpiece();
    vector<int> getposn();
    bool verify(Piece t, Color p);
    void changeposn(vector<int> posn);
    virtual ~basicpiece();
    virtual vector<step> validmoves() = 0;
    virtual vector<step> moves() = 0;
    //the move that still puts king in check is also invald
    //this is used to check the situation of checkmate.
    virtual bool isvalid(vector<int>) = 0;
    virtual bool ismovable(vector<int>) = 0;
};


#endif /* basicpiece_h */
