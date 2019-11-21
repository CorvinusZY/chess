//
//  knight.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "knight.h"
#include "game.h"
#include "step.h"
knight::knight(knight &other) {
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;
}
knight *knight::duplicate() {
    return new knight(*this);
}

knight::knight(Color p, vector<int> posn, game *thegame) {
    position = posn;
    type = Piece::KN;
    player = p;
    mygame = thegame;
}

bool knight::isvalid(vector<int> target) {
    for (int x=0; x<validmoves().size(); x++) {
        if (target == validmoves().at(x).target) {return true;}
    }
    return false;
}

vector<step> knight::validmoves() {
    vector<step> valids{};
    step spot1 = {position, vector<int>{position[0]+2, position[1]+1}};
    step spot2 = {position, vector<int>{position[0]+2, position[1]-1}};
    step spot3 = {position, vector<int>{position[0]-2, position[1]+1}};
    step spot4 = {position, vector<int>{position[0]-2, position[1]-1}};
    step spot5 = {position, vector<int>{position[0]+1, position[1]+2}};
    step spot6 = {position, vector<int>{position[0]+1, position[1]-2}};
    step spot7 = {position, vector<int>{position[0]-1, position[1]+2}};
    step spot8 = {position, vector<int>{position[0]-1, position[1]-2}};
    
    if(checkstep(spot1, mygame)) {valids.emplace_back(spot1);}
    if(checkstep(spot2, mygame)) {valids.emplace_back(spot2);}
    if(checkstep(spot3, mygame)) {valids.emplace_back(spot3);}
    if(checkstep(spot4, mygame)) {valids.emplace_back(spot4);}
    if(checkstep(spot5, mygame)) {valids.emplace_back(spot5);}
    if(checkstep(spot6, mygame)) {valids.emplace_back(spot6);}
    if(checkstep(spot7, mygame)) {valids.emplace_back(spot7);}
    if(checkstep(spot8, mygame)) {valids.emplace_back(spot8);}
    
    
    return valids;
}
vector<step> knight::moves() {
    vector<step> valids{};
    step spot1 = {position, vector<int>{position[0]+2, position[1]+1}};
    step spot2 = {position, vector<int>{position[0]+2, position[1]-1}};
    step spot3 = {position, vector<int>{position[0]-2, position[1]+1}};
    step spot4 = {position, vector<int>{position[0]-2, position[1]-1}};
    step spot5 = {position, vector<int>{position[0]+1, position[1]+2}};
    step spot6 = {position, vector<int>{position[0]+1, position[1]-2}};
    step spot7 = {position, vector<int>{position[0]-1, position[1]+2}};
    step spot8 = {position, vector<int>{position[0]-1, position[1]-2}};
    
    if(checkstep_nocheck(spot1, mygame)) {valids.emplace_back(spot1);}
    if(checkstep_nocheck(spot2, mygame)) {valids.emplace_back(spot2);}
    if(checkstep_nocheck(spot3, mygame)) {valids.emplace_back(spot3);}
    if(checkstep_nocheck(spot4, mygame)) {valids.emplace_back(spot4);}
    if(checkstep_nocheck(spot5, mygame)) {valids.emplace_back(spot5);}
    if(checkstep_nocheck(spot6, mygame)) {valids.emplace_back(spot6);}
    if(checkstep_nocheck(spot7, mygame)) {valids.emplace_back(spot7);}
    if(checkstep_nocheck(spot8, mygame)) {valids.emplace_back(spot8);}
    
    
    return valids;

}
bool knight::ismovable(vector<int>target) {
    for (int x=0; x<moves().size(); x++) {
        if (target == moves().at(x).target) {return true;}
    }
    return false;

}
