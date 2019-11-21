//
//  biship.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "biship.h"
#include "game.h"
#include "step.h"

biship::biship(biship &other) {
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;

}
biship *biship::duplicate() {
    return new biship(*this);
}
biship::biship(Color p, vector<int> posn, game* thegame) {
    position = posn;
    type = Piece::B;
    player = p;
    mygame = thegame;
}

bool biship::isvalid(vector<int>target)  {
    for (int x=0; x<validmoves().size(); x++) {
        if (target == validmoves().at(x).target) {return true;}
    }
    return false;
}
vector<step> biship::validmoves() {
    vector<step> valids{};
    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    //int i = 0;
    
    findline(valids, topleft, -1, -1, mygame);
    findline(valids, bottomleft, 1, -1, mygame);
    findline(valids, topright, -1, 1, mygame);
    findline(valids, bottomright, 1, 1, mygame);
    return valids;
    
}

vector<step> biship::moves() {
    vector<step> valids{};
    step topleft = {position, vector<int>{position[0]-1, position[1]-1}};
    step bottomleft = {position, vector<int>{position[0]+1, position[1]-1}};
    step topright = {position, vector<int>{position[0]-1, position[1]+1}};
    step bottomright = {position, vector<int>{position[0]+1, position[1]+1}};
    //int i = 0;
    
    findline_nocheck(valids, topleft, -1, -1, mygame);
    findline_nocheck(valids, bottomleft, 1, -1, mygame);
    findline_nocheck(valids, topright, -1, 1, mygame);
    findline_nocheck(valids, bottomright, 1, 1, mygame);
    return valids;

}
bool biship::ismovable(vector<int>target) {
    for (int x=0; x<moves().size(); x++) {
        if (target == moves().at(x).target) {return true;}
    }
    return false;
}

