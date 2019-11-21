//
//  pawn.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "pawn.h"
#include "game.h"
#include "step.h"
pawn::pawn(pawn &other) {
    initial = other.initial;
    initial2 = other.initial2;
    position = other.position;
    type = other.type;
    player = other.player;
    mygame = other.mygame;
    EP = other.EP;
}
pawn *pawn::duplicate() {
    return new pawn(*this);
}


pawn::pawn(Color p, vector<int> posn, game *thegame) {
    initial = false;
    initial2 = false;
    position = posn;
    type = Piece::P;
    player = p;
    mygame = thegame;
    EP = "";
}

bool pawn::justinitial2() {
    return initial2;
}

void pawn::deinitial2() {
    initial2 = false;
}

void pawn::initialize(int moves) {
    initial = true;
    if(moves == 2) {
        initial2 = true;
    }
}

bool pawn::isvalid(vector<int> target) {
    vector<step> mymoves = validmoves();
    for (int x=0; x<mymoves.size(); x++) {
        if (target == mymoves.at(x).target) {
            if ((target.at(0) == position[0]+2)||(target.at(0) == position[0]-2)) {
                throw string{"PAWN INITIAL2"};
            }
            if (initial == false){
                initialize(1);
            }
            
            if ((target.at(1) != position[1]) && (!mygame->getpiece(target))) {
                if(mygame->getcurr() == Color::black) {
                    throw string{"BLACK EN PASSANT"};
                } else {
                    throw string{"WHITE EN PASSANT"};
                }
                
            } else {
                return true;
            }
        }
    }
    return false;
}

vector<step> pawn::validmoves() {
    
    vector<step> valids;
    step initial1;
    step initial2;
    step captureleft;
    step captureright;
    
    if(getcolor() == Color::black) {
        initial1 = {position, vector<int>{position[0]-1, position[1]}};
        initial2 = {position, vector<int>{position[0]-2, position[1]}};
        captureleft = {position, vector<int>{position[0]-1, position[1]-1}};
        captureright = {position, vector<int>{position[0]-1, position[1]+1}};
    } else {
        initial1 = {position, vector<int>{position[0]+1, position[1]}};
        initial2 = {position, vector<int>{position[0]+2, position[1]}};
        captureleft = {position, vector<int>{position[0]+1, position[1]-1}};
        captureright = {position, vector<int>{position[0]+1, position[1]+1}};
    }
    
    if((checkstep(initial1, mygame))&&(!mygame->getpiece(initial1.target))) {
        if(!mygame->getpiece(initial1.target))valids.emplace_back(initial1);
    }
    if((initial == false) &&
       (!mygame->getpiece(initial1.target))&&
       (!mygame->getpiece(initial2.target))&&
       (checkstep(initial2, mygame))) {
        valids.emplace_back(initial2);
    }
    if(checkstep(captureleft, mygame)){
        if((!mygame->getpiece(captureleft.target))) {
            vector<int> strictleft{position.at(0), position.at(1)-1};
            if((mygame->getpiece(strictleft))&&(mygame->getpiece(strictleft)->getpiece() == Piece::P) && (mygame->getpiece(strictleft)->justinitial2())) {
                valids.emplace_back(captureleft);
            }
        }
        else {
            if(mygame->getpiece(captureleft.target)->getcolor() != mygame->getpiece(captureright.origin)->getcolor()) {
                valids.emplace_back(captureleft);
            }
        }
    }
    if(checkstep(captureright, mygame)) {
        //if(inrange(captureright.target)) {cout<<"inrange"<<endl;}
        if((!mygame->getpiece(captureright.target))) {
            vector<int> strictright{position.at(0), position.at(1)+1};
            if((mygame->getpiece(strictright))&&(mygame->getpiece(strictright)->getpiece() == Piece::P) && (mygame->getpiece(strictright)->justinitial2())) {
                valids.emplace_back(captureright);
            }
        }
        else {
            if(mygame->getpiece(captureright.target)->getcolor() != mygame->getpiece(captureright.origin)->getcolor()) {
                valids.emplace_back(captureright);
            }
        }
    }


    
    return valids;
}
vector<step> pawn::moves() {
    vector<step> valids;
    step initial1;
    step initial2;
    step captureleft;
    step captureright;
    
    if(getcolor() == Color::black) {
        initial1 = {position, vector<int>{position[0]-1, position[1]}};
        initial2 = {position, vector<int>{position[0]-2, position[1]}};
        captureleft = {position, vector<int>{position[0]-1, position[1]-1}};
        captureright = {position, vector<int>{position[0]-1, position[1]+1}};
    } else {
        initial1 = {position, vector<int>{position[0]+1, position[1]}};
        initial2 = {position, vector<int>{position[0]+2, position[1]}};
        captureleft = {position, vector<int>{position[0]+1, position[1]-1}};
        captureright = {position, vector<int>{position[0]+1, position[1]+1}};
    }
    
    if(checkstep_nocheck(initial1, mygame)) {
        if(!mygame->getpiece(initial1.target))valids.emplace_back(initial1);
    }
    if((initial == false) &&
       (!mygame->getpiece(initial1.target))&&
       (checkstep_nocheck(initial2, mygame))) {
        valids.emplace_back(initial2);
    }
    if(checkstep_nocheck(captureleft, mygame)){
        if((!mygame->getpiece(captureleft.target))) {
            vector<int> strictleft{position.at(0), position.at(1)-1};
            if((mygame->getpiece(strictleft))&&(mygame->getpiece(strictleft)->getpiece() == Piece::P) && (mygame->getpiece(strictleft)->justinitial2())) {
                valids.emplace_back(captureleft);
            }
        }
        else {
            if(mygame->getpiece(captureleft.target)->getcolor() != mygame->getpiece(captureright.origin)->getcolor()) {
                valids.emplace_back(captureleft);
            }
        }
    }
    if(checkstep_nocheck(captureright, mygame)) {
        //if(inrange(captureright.target)) {cout<<"inrange"<<endl;}
        if((!mygame->getpiece(captureright.target))) {
            vector<int> strictright{position.at(0), position.at(1)+1};
            if((mygame->getpiece(strictright))&&(mygame->getpiece(strictright)->getpiece() == Piece::P) && (mygame->getpiece(strictright)->justinitial2())) {
                valids.emplace_back(captureright);
            }
        }
        else {
            if(mygame->getpiece(captureright.target)->getcolor() != mygame->getpiece(captureright.origin)->getcolor()) {
                valids.emplace_back(captureright);
            }
        }
    }
    
    
    
    return valids;
}
bool pawn::ismovable(vector<int>target) {
    vector<step> mymoves = moves();
    for (int x=0; x<mymoves.size(); x++) {
        if (target == mymoves.at(x).target) {
            if ((target.at(0) == position[0]+2)||(target.at(0) == position[0]-2)) {
                //throw string{"PAWN INITIAL2"};
            }
            if (initial == false){
                initialize(1);
            }
            
            if ((target.at(1) != position[1]) && (!mygame->getpiece(target))) {
                if(mygame->getcurr() == Color::black) {
                    //throw string{"BLACK EN PASSANT"};
                } else {
                    //throw string{"WHITE EN PASSANT"};
                }
                
            } else {
                return true;
            }
        }
    }
    return false;

}
void pawn::setEP(string ep) {EP = ep;}
