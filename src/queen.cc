//
//  queen.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "queen.h"
#include "game.h"
#include "step.h"
queen::queen(queen &other) {
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;
}
queen *queen::duplicate() {
    return new queen(*this);
}


queen::queen(Color p, vector<int> posn, game *thegame) {
    position = posn;
    type = Piece::Q;
    player = p;
    mygame = thegame;
}


bool queen::isvalid(vector<int> target) {
    for (int x=0; x<validmoves().size(); x++) {
        if (target == validmoves().at(x).target) {return true;}
    }
    return false;
}

vector<step> queen::validmoves() {
    
    
    vector<step> valids{};
    step top = {position, vector<int>{position[0]-1, position[1]+0}};
    step bottom = {position, vector<int>{position[0]+1, position[1]+0}};
    step left = {position, vector<int>{position[0]+0, position[1]-1}};
    step right = {position, vector<int>{position[0]+0, position[1]+1}};

    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    
    findline(valids, top, -1, 0, mygame);
    findline(valids, bottom, 1, 0, mygame);
    findline(valids, left, 0, -1, mygame);
    findline(valids, right, 0, 1, mygame);
    
    findline(valids, topleft, -1, -1, mygame);
    findline(valids, bottomleft, 1, -1, mygame);
    findline(valids, topright, -1, 1, mygame);
    findline(valids, bottomright, 1, 1, mygame);
    return valids;

    
}

vector<step> queen::moves(){
    
    vector<step> valids{};
    step top = {position, vector<int>{position[0]-1, position[1]+0}};
    step bottom = {position, vector<int>{position[0]+1, position[1]+0}};
    step left = {position, vector<int>{position[0]+0, position[1]-1}};
    step right = {position, vector<int>{position[0]+0, position[1]+1}};
    
    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    
    findline_nocheck(valids, top, -1, 0, mygame);
    findline_nocheck(valids, bottom, 1, 0, mygame);
    findline_nocheck(valids, left, 0, -1, mygame);
    findline_nocheck(valids, right, 0, 1, mygame);
    
    findline_nocheck(valids, topleft, -1, -1, mygame);
    findline_nocheck(valids, bottomleft, 1, -1, mygame);
    findline_nocheck(valids, topright, -1, 1, mygame);
    findline_nocheck(valids, bottomright, 1, 1, mygame);
    return valids;

}
bool queen::ismovable(vector<int>target){
    for (int x=0; x<moves().size(); x++) {
        if (target == moves().at(x).target) {return true;}
    }
    return false;
}
