//
//  king.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "king.h"
#include "game.h"
#include "step.h"
king::king(king &other) {
    initial = other.initial;
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;
}
king *king::duplicate() {
    king* copy =new king(*this);
    return copy;
}

king::king(Color p, vector<int> posn, game *thegame) {
    initial = false;
    position = posn;
    type = Piece::K;
    player = p;
    mygame = thegame;
}

bool king::isvalid(vector<int> target) {
    for (int x=0; x<validmoves().size(); x++) {
        if (target == validmoves().at(x).target) {
            if(initial == false) {initialize(1);}
            
            if(target.at(1) == position.at(1)-2) {throw string{"LEFT CASTLING"};}
            else if (target.at(1) == position.at(1)+2) {throw string{"RIGHT CASTLING"};}
            
            return true;
        }
    }
    return false;
}

void king::initialize(int moves) {
    initial = true;
}

bool king::isinitial() {return initial;}

vector<step> king::validmoves() {
    vector<step> valids;
    
    step top = {position, vector<int>{position[0]-1, position[1]}};
    step bottom = {position, vector<int>{position[0]+1, position[1]}};
    step left = {position, vector<int>{position[0], position[1]-1}};
    step right = {position, vector<int>{position[0], position[1]+1}};
    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    step leftcastling = {position, vector<int>{position[0], position[1]-2}};
    step rightcastling = {position, vector<int>{position[0], position[1]+2}};
    
    if(checkstep(top, mygame)) {valids.emplace_back(top);}
    if(checkstep(bottom, mygame)) {valids.emplace_back(bottom);}
    if(checkstep(left, mygame)) {valids.emplace_back(left);}
    if(checkstep(right, mygame)) {valids.emplace_back(right);}
    if(checkstep(topleft, mygame)) {valids.emplace_back(topleft);}
    if(checkstep(bottomleft, mygame)) {valids.emplace_back(bottomleft);}
    if(checkstep(topright, mygame)) {valids.emplace_back(topright);}
    if(checkstep(bottomright, mygame)) {valids.emplace_back(bottomright);}
    
    if((initial == false)&&
       (mygame->getpiece(vector<int>{position.at(0), 0}))&&
       (mygame->getpiece(vector<int>{position.at(0), 0})->getpiece() == Piece::R)&&
       (!mygame->getpiece(vector<int>{position.at(0), 0})->isinitial())) {
        if((!mygame->getpiece(vector<int>{position.at(0), 1}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 2}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 3}) )) {
            if(checkstep(leftcastling, mygame)){valids.emplace_back(leftcastling);}
        }
    }
    
    if((initial == false)&&
       (mygame->getpiece(vector<int>{position.at(0), 7}))&&
       (mygame->getpiece(vector<int>{position.at(0), 7})->getpiece() == Piece::R)&&
       (!mygame->getpiece(vector<int>{position.at(0), 7})->isinitial())) {
        if((!mygame->getpiece(vector<int>{position.at(0), 6}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 5}) )) {
            if(checkstep(leftcastling, mygame)){valids.emplace_back(rightcastling);}
        }
    }

    
    return valids;
    
}

vector<step> king::moves() {
    vector<step> valids;
    
    step top = {position, vector<int>{position[0]-1, position[1]}};
    step bottom = {position, vector<int>{position[0]+1, position[1]}};
    step left = {position, vector<int>{position[0], position[1]-1}};
    step right = {position, vector<int>{position[0], position[1]+1}};
    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    step leftcastling = {position, vector<int>{position[0], position[1]-2}};
    step rightcastling = {position, vector<int>{position[0], position[1]+2}};
    
    if(checkstep_nocheck(top, mygame)) {valids.emplace_back(top);}
    if(checkstep_nocheck(bottom, mygame)) {valids.emplace_back(bottom);}
    if(checkstep_nocheck(left, mygame)) {valids.emplace_back(left);}
    if(checkstep_nocheck(right, mygame)) {valids.emplace_back(right);}
    if(checkstep_nocheck(topleft, mygame)) {valids.emplace_back(topleft);}
    if(checkstep_nocheck(bottomleft, mygame)) {valids.emplace_back(bottomleft);}
    if(checkstep_nocheck(topright, mygame)) {valids.emplace_back(topright);}
    if(checkstep_nocheck(bottomright, mygame)) {valids.emplace_back(bottomright);}
    
    if((initial == false)&&
       (mygame->getpiece(vector<int>{position.at(0), 0}))&&
       (mygame->getpiece(vector<int>{position.at(0), 0})->getpiece() == Piece::R)&&
       (!mygame->getpiece(vector<int>{position.at(0), 0})->isinitial())) {
        if((!mygame->getpiece(vector<int>{position.at(0), 1}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 2}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 3}) )) {
            if(checkstep_nocheck(leftcastling, mygame)){valids.emplace_back(leftcastling);}
        }
    }
    
    if((initial == false)&&
       (mygame->getpiece(vector<int>{position.at(0), 7}))&&
       (mygame->getpiece(vector<int>{position.at(0), 7})->getpiece() == Piece::R)&&
       (!mygame->getpiece(vector<int>{position.at(0), 7})->isinitial())) {
        if((!mygame->getpiece(vector<int>{position.at(0), 6}) )&&
           (!mygame->getpiece(vector<int>{position.at(0), 5}) )) {
            if(checkstep_nocheck(leftcastling, mygame)){valids.emplace_back(rightcastling);}
        }
    }
    
    
    return valids;
}
bool king::ismovable(vector<int>target) {
    for (int x=0; x<moves().size(); x++) {
        if (target == moves().at(x).target) {
            if(initial == false) {initialize(1);}
            
            //if(target.at(1) == position.at(1)-2) {throw string{"LEFT CASTLING"};}
            //else if (target.at(1) == position.at(1)+2) {throw string{"RIGHT CASTLING"};}
            
            return true;
        }
    }
    return false;
}


