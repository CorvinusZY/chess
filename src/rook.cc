//
//  rook.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "rook.h"
#include "game.h"
#include "step.h"
rook::rook(rook &other) {
    initial = other.initial;
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;
}
rook *rook::duplicate() {
    return new rook(*this);
}

rook::rook(Color p, vector<int> posn, game *thegame) {
    initial = false;
    position = posn;
    type = Piece::R;
    player = p;
    mygame = thegame;
}

void rook::initialize(int moves) {
    initial = true;
}

bool rook::isinitial() {return initial;}

bool rook::isvalid(vector<int> target) {
    for (int x=0; x<validmoves().size(); x++) {
        if (target == validmoves().at(x).target) {
            if(initial == false) {initialize(1);}
            return true;
        }
    }
    return false;
}
vector<step> rook::validmoves() {
    vector<step> valids;
    
    step top = {position, vector<int>{position[0]-1, position[1]+0}};
    step bottom = {position, vector<int>{position[0]+1, position[1]+0}};
    step left = {position, vector<int>{position[0]+0, position[1]-1}};
    step right = {position, vector<int>{position[0]+0, position[1]+1}};
    
    
    findline(valids, top, -1, 0, mygame);
    findline(valids, bottom, 1, 0, mygame);
    findline(valids, left, 0, -1, mygame);
    findline(valids, right, 0, 1, mygame);
    /*if(getcolor() == Color::black) {
        cout <<"size"<<valids.size()<<endl;
        for(int i=0; i<valids.size();i++) {
            cout <<"from"<<valids[i].origin[0]<<valids[i].origin[1];
            cout<<"to"<<valids[i].target[0]<<valids[i].target[1]<<endl;
        }
    }*/
    
    return valids;
}

vector<step> rook::moves() {
    vector<step> valids;
    
    step top = {position, vector<int>{position[0]-1, position[1]+0}};
    step bottom = {position, vector<int>{position[0]+1, position[1]+0}};
    step left = {position, vector<int>{position[0]+0, position[1]-1}};
    step right = {position, vector<int>{position[0]+0, position[1]+1}};
    
    
    findline_nocheck(valids, top, -1, 0, mygame);
    findline_nocheck(valids, bottom, 1, 0, mygame);
    findline_nocheck(valids, left, 0, -1, mygame);
    findline_nocheck(valids, right, 0, 1, mygame);
    /*if(getcolor() == Color::black) {
     cout <<"size"<<valids.size()<<endl;
     for(int i=0; i<valids.size();i++) {
     cout <<"from"<<valids[i].origin[0]<<valids[i].origin[1];
     cout<<"to"<<valids[i].target[0]<<valids[i].target[1]<<endl;
     }
     }*/
    
    return valids;
}
bool rook::ismovable(vector<int>target) {
    for (int x=0; x<moves().size(); x++) {
        if (target == moves().at(x).target) {
            if(initial == false) {initialize(1);}
            return true;
            
        }
    }
    return false;
}
