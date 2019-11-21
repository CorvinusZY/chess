//
//  basicpiece.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "basicpiece.h"
#include "step.h"
void basicpiece::setgame(game *thegame) {mygame = thegame;}
bool basicpiece::verify(Piece t, Color p) {
    if((player == p)&&(type == t)) return true;
    else return false;
}
Color basicpiece::getcolor() {return player;}
Piece basicpiece::getpiece() {return type;}
vector<int> basicpiece::getposn() {return position;}
void basicpiece::changeposn(vector<int>posn) {position = posn;}
basicpiece::~basicpiece() {}
bool basicpiece::justinitial2() {//function has no purpose in basicpiece
    return false;
}
void basicpiece::initialize(int moves) {};
void basicpiece::deinitial2() {}
bool basicpiece::isinitial() {
    return false;
}
