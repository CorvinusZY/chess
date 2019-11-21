//
//  game.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "game.h"

game::game(bool humanVH, bool humanVC, bool computerVC, int level1, int level2, Color currplayer)
:humanVC(humanVC), humanVH(humanVH), computerVC(computerVC), currplayer(currplayer) {
    if(level1>0)AI1 = new computer(level1, this);
    else AI1 = nullptr;
    
    if(level2>0)AI2 = new computer(level2, this);
    else AI2 = nullptr;
    
    mydisplay = new display(this);
}

game::game(const game &other){
    humanVH = false;
    humanVC = false;
    computerVC = false;
    currplayer = other.currplayer;
    board = {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if(other.board.at(i).at(j)){
                board.at(i).at(j) = other.board.at(i).at(j)->duplicate();
                board.at(i).at(j)->setgame(this);
            }
        }
    }
    
    AI1 = nullptr;
    AI2 = nullptr;
    mydisplay = nullptr;
}

step game:: AIMove(int ainum){
    if (ainum == 1){
        return AI1->bestMove();
    }else{
        return AI2->bestMove();
    }
}

bool game::setupdone() {
    
    int blackking = 0;
    int whiteking = 0;
    for (int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(board.at(i).at(j)) {
                if(board.at(i).at(j)->getpiece() == Piece::K) {
                    if(board.at(i).at(j)->getcolor() == Color::black) {
                        blackking++;
                    } else {
                        whiteking++;
                    }
                }
                
                if(board.at(i).at(j)->getpiece() == Piece::P) {
                    if((i == 0)||(i == 7)) {return false;}
                }
            }
            
        }
    }
    
    if((blackking != 1)||(whiteking != 1)) {return false;}
    if(blackisCheck() || whiteisCheck()) {
        return false;
    }
    
    return true;
}

void game::initial() {//coordinate (0,0) corresponds a1
    initialized = true;
    
    if(!issetup){
        board = {
            {new rook(Color::white, vector<int>{0,0}, this),
                new knight(Color::white,  vector<int>{0,1}, this),
                new biship(Color::white,  vector<int>{0,2}, this),
                new queen(Color::white,  vector<int>{0,3}, this),
                new king(Color::white,  vector<int>{0,4}, this),
                new biship(Color::white,  vector<int>{0,5},this),
                new knight(Color::white,  vector<int>{0,6}, this),
                new rook(Color::white, vector<int>{0,7}, this)},
            {new pawn(Color::white, vector<int>{1,0}, this),
                new pawn(Color::white, vector<int>{1,1}, this),
                new pawn(Color::white, vector<int>{1,2}, this),
                new pawn(Color::white, vector<int>{1,3}, this),
                new pawn(Color::white, vector<int>{1,4}, this),
                new pawn(Color::white, vector<int>{1,5}, this),
                new pawn(Color::white, vector<int>{1,6}, this),
                new pawn(Color::white, vector<int>{1,7}, this)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            
            {new pawn(Color::black, vector<int>{6,0}, this),
                new pawn(Color::black, vector<int>{6,1}, this),
                new pawn(Color::black, vector<int>{6,2}, this),
                new pawn(Color::black, vector<int>{6,3}, this),
                new pawn(Color::black, vector<int>{6,4}, this),
                new pawn(Color::black, vector<int>{6,5}, this),
                new pawn(Color::black, vector<int>{6,6}, this),
                new pawn(Color::black, vector<int>{6,7}, this)},
            {new rook(Color::black,vector<int>{7,0}, this),
                new knight(Color::black, vector<int>{7,1}, this),
                new biship(Color::black, vector<int>{7,2}, this),
                new queen(Color::black, vector<int>{7,3}, this),
                new king(Color::black, vector<int>{7,4}, this),
                new biship(Color::black, vector<int>{7,5}, this),
                new knight(Color::black, vector<int>{7,6}, this),
                new rook(Color::black, vector<int>{7,7}, this)}};
        
    }
}

game::~game() {
    for(int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            delete board.at(i).at(j);
        }
    }
    
    delete mydisplay;
    if(AI1)delete AI1;
    if(AI2)delete AI2;
}


void game::addComputer(int num, int diff){
    computer* ai = new computer(diff, this);
    if(num == 1){
        this->AI1 = ai;
    }else{
        this->AI2 = ai;
    }
    return;
}

Color game::whoWon() {
    if(blackisCheckmate()) {return Color::white;}
    if(whiteisCheckmate()) {return Color::black;}
    return Color::white;
}

bool game::isWon(){
    if(blackisCheckmate() || whiteisCheckmate()) return true;
    return false;
}

bool game::blackisCheck(){
    basicpiece *blackking = gettype(Color::black, Piece::K);
        for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            basicpiece *curr = board.at(i).at(j);
            if(curr) {//for non-nullptr pieces
                if(curr->getcolor() == Color::white) {
                    if(curr->ismovable(blackking->getposn())) return true;
                }
            }
        }
    }
    return false;
}

bool game::whiteisCheck() {
    basicpiece *whiteking = gettype(Color::white, Piece::K);
    for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            basicpiece *curr = board.at(i).at(j);
            if(curr) {//for non-nullptr pieces
                if(curr->getcolor() == Color::black) {
                    if(curr->ismovable(whiteking->getposn())) return true;
                }
            }
        }
    }
    return false;
}

bool game::whiteisCheckmate(){
    if(whiteisCheck()) {
        if(whitevalids().size() == 0) return true;
    }
    return false;
}

bool game::blackisCheckmate() {
    if(blackisCheck()) {
        if(blackvalids().size() == 0) return true;
    }
    return false;
}
bool game::isStalemate(){
    if(currplayer == Color::black){
        if(!blackisCheck() && (blackvalids().size() == 0)) {
            return true;
        }
    }
    if(currplayer == Color::white) {
        if(!whiteisCheck() && (whitevalids().size() == 0)) {
            return true;
        }
    }
    
    return false;
}

vector<step> game::blackvalids(){
    vector<step> valids{};
    for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if((board.at(i).at(j))&&
               board.at(i).at(j)->getcolor() == Color::black) {
                vector<step> tmp = board.at(i).at(j)->validmoves();
                for(int x = 0; x<tmp.size(); x++) {
                    /*if(getpiece(tmp.at(x).origin)->getpiece() == Piece::P) {
                        cout<<"pawn from"<<tmp.at(x).origin[0]<<tmp.at(x).origin[1];
                        cout<<" to"<<tmp.at(x).target[0]<<tmp.at(x).target[1]<<endl;
                    }*/
                    valids.emplace_back(tmp.at(x));
                }
            }
        }
    }
    return valids;
}

void game::entersetup() {
    issetup = true;
    board = {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
    
}//denotes the game with setup board
void game::setup(vector<int> target) {
    delete getpiece(target);
    board.at(target[0]).at(target[1]) = nullptr;
}//deletes a piece in a specific spot
void game::setup(vector<int> target, Piece type, Color player) {
    delete getpiece(target);
    if(type == Piece::K){board.at(target[0]).at(target[1]) = new king(player, target, this);}
    if(type == Piece::R){board.at(target[0]).at(target[1]) = new rook(player, target, this);}
    if(type == Piece::Q){board.at(target[0]).at(target[1]) = new queen(player, target, this);}
    if(type == Piece::KN){board.at(target[0]).at(target[1]) = new knight(player, target, this);}
    if(type == Piece::P){board.at(target[0]).at(target[1]) = new pawn(player, target, this);}
    if(type == Piece::B){board.at(target[0]).at(target[1]) = new biship(player, target, this);}
    
}//places a piece in a specific spot

vector<step> game::whitevalids(){
    vector<step> valids{};
    for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if((board.at(i).at(j))&&(board.at(i).at(j)->getcolor() == Color::white)) {
                vector<step> tmp = board.at(i).at(j)->validmoves();
                for(int x = 0; x<tmp.size(); x++) {
                    valids.emplace_back(tmp.at(x));
                }
            }
        }
    }
    return valids;
}

basicpiece *game::gettype(Color player, Piece type) {
    for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if((board.at(i).at(j))&&(board.at(i).at(j)->verify(type, player) == true)) {
                return board.at(i).at(j);
            }
        }
    }
    return nullptr;
}

basicpiece *game::getpiece(vector<int> dest){
    basicpiece *tmp = board.at(dest[0]).at(dest[1]);
    return tmp;
}

Color game::getcurr() {return currplayer;}
void game::setplayer(Color curr) {currplayer = curr;}
void game::displayboard() {
    mydisplay->charplay();
}
void game::promoteP(vector<int> origin, vector<int> target, string promote) {
    if((origin.at(0) > 7)||(origin.at(0)<0)||(origin.at(1)>7)||(origin.at(1)<0)){
        throw string{"INVALIDPOSN"};
    }
    if((target.at(0) > 7)||(target.at(0)<0)||(target.at(1)>7)||(target.at(1)<0)){
        throw string{"INVALIDPOSN"};
    }
    basicpiece *tmp = getpiece(origin);
    bool isvalid = true;
    isvalid = tmp->isvalid(target);
    
    if(((tmp->getcolor() == Color::black)&&(target.at(0) == 0)) ||
       ((tmp->getcolor() == Color::white)&&(target.at(0) == 7))) {
        if(isvalid) {
            if(promote == "Q") {
                basicpiece *newpiece = new queen(tmp->getcolor(), target, this);
                board.at(target[0]).at(target[1]) = newpiece;
                newpiece->changeposn(target);
            }
            else if (promote == "B") {
                basicpiece *newpiece = new biship(tmp->getcolor(), target, this);
                board.at(target[0]).at(target[1]) = newpiece;
                newpiece->changeposn(target);
            }
            else if (promote == "KN") {
                basicpiece *newpiece = new knight(tmp->getcolor(), target, this);
                board.at(target[0]).at(target[1]) = newpiece;
                newpiece->changeposn(target);
            }
            else if (promote == "R") {
                basicpiece *newpiece = new rook(tmp->getcolor(), target, this);
                board.at(target[0]).at(target[1]) = newpiece;
                newpiece->changeposn(target);
            }
            delete tmp;
            board.at(origin[0]).at(origin[1]) = nullptr;
            displayboard();
            if(getcurr() == Color::white) {currplayer = Color::black;}
            else {currplayer = Color::white;}
        }
    } else {throw string{"INVALIDMOVE"};}
    
    if(!isvalid) {throw string{"INVALIDMOVE"};}
}

void game::move(vector<int> origin, vector<int> target, Color player){
    //cout <<"move"<<origin[0]<<origin[1]<<"to"<<target[0]<<target[1]<<endl;
    ///check if coordinates entered are on the board
    if((origin.at(0) > 7)||(origin.at(0)<0)||(origin.at(1)>7)||(origin.at(1)<0)){
        throw string{"INVALIDPOSN"};
    }
    if((target.at(0) > 7)||(target.at(0)<0)||(target.at(1)>7)||(target.at(1)<0)){
        throw string{"INVALIDPOSN"};
    }
    bool isvalid = true;
    basicpiece *tmp = getpiece(origin);
    
    if ((!tmp)||(player != tmp->getcolor())) {throw string{"INVALIDMOVE"};}//check player identity
    try {
        isvalid = tmp->isvalid(target);
        //cout <<"step reached1"<<endl;
        if(isvalid) {//isvalid is going to throw a string if this is special case
            delete board.at(target[0]).at(target[1]);
            board.at(target[0]).at(target[1]) = tmp;
            tmp->changeposn(target);
            board.at(origin[0]).at(origin[1]) = nullptr;
            if(getcurr() == Color::white) {currplayer = Color::black;}
            else {currplayer = Color::white;}
            
            for(int x=0; x<pawn_initial2.size(); x++) {
                if(initial_time.at(x) == 0) {
                    initial_time.at(x) = 1;
                } else if (initial_time.at(x) == 1) {
                    initial_time.at(x) = -1;
                    if(getpiece(pawn_initial2.at(x)))
                        getpiece(pawn_initial2.at(x))->deinitial2();
                }
            }
            displayboard();
            //cout <<"board displayed"<<endl;
        }
    }
    catch (string exp) {
        if(exp == "PAWN INITIAL2") {//a pawn moves 2 steps in its initial step
            tmp->initialize(2);
            int time = 0;
            
            initial_time.emplace_back(time);
            pawn_initial2.emplace_back(target);
            delete board.at(target[0]).at(target[1]);
            board.at(target[0]).at(target[1]) = tmp;
            tmp->changeposn(target);
            board.at(origin[0]).at(origin[1]) = nullptr;
        }
        else if(exp == "BLACK EN PASSANT") {//black captures white
            delete board.at(target[0]).at(target[1]);
            board.at(target[0]).at(target[1]) = tmp;
            tmp->changeposn(target);
            board.at(origin[0]).at(origin[1]) = nullptr;
            delete board.at(target[0]+1).at(target[1]);
            board.at(target[0]+1).at(target[1]) = nullptr;
        }
        else if (exp == "WHITE EN PASSANT") {//white captures black
            delete board.at(target[0]).at(target[1]);
            board.at(target[0]).at(target[1]) = tmp;
            tmp->changeposn(target);
            board.at(origin[0]).at(origin[1]) = nullptr;
            delete board.at(target[0]-1).at(target[1]);
            board.at(target[0]-1).at(target[1]) = nullptr;
        }
        else if (exp == "LEFT CASTLING") {//king moves towards left
            
            board.at(target[0]).at(target[1]) = tmp;
            tmp->changeposn(target);
            board.at(origin[0]).at(origin[1]) = nullptr;
            board.at(target[0]).at(target[1]+1) = board.at(target[0]).at(0);
            vector<int> rooknewposn{target[0], target[1]+1};
            board.at(target[0]).at(target[1]+1)->changeposn(rooknewposn);
            board.at(target[0]).at(0) = nullptr;
        }
        else if (exp == "RIGHT CASTLING") {//towards right
            
            board.at(target[0]).at(target[1]) = tmp;
            board.at(origin[0]).at(origin[1]) = nullptr;
            board.at(target[0]).at(target[1]-1) = board.at(target[0]).at(7);
            vector<int> rooknewposn{target[0], target[1]-1};
            board.at(target[0]).at(target[1]-1)->changeposn(rooknewposn);
            board.at(target[0]).at(7) = nullptr;
        }
        //case of promoting pawn is handled directly in the method promoteP()
        
        
        for(int x=0; x<pawn_initial2.size(); x++) {
            if(initial_time.at(x) == 0) {
                initial_time.at(x) = 1;
            } else if (initial_time.at(x) == 1) {
                initial_time.at(x) = -1;
                if(getpiece(pawn_initial2.at(x)))
                    getpiece(pawn_initial2.at(x))->deinitial2();
            }
        }
        
        
        if(getcurr() == Color::white) {currplayer = Color::black;}
        else {currplayer = Color::white;}
        displayboard();
    }
    //cout<<"end stack"<<endl;
    if(!isvalid) {throw string{"INVALIDMOVE"};}
    //cout<<"end stack"<<endl;
}


///helper functions


bool inrange(vector<int> target) {
    if((target.at(0) > 7)||(target.at(0)<0)||(target.at(1)>7)||(target.at(1)<0)) {
        return false;
    }
    return true;
}

void findline_nocheck(vector<step> &valids, step currentline, int y, int x, game *mygame)
{
    while(true) {
        if(inrange(currentline.target)) {
            if(!mygame->getpiece(currentline.target)) {
                //encountering blank spot
                valids.emplace_back(currentline);
                currentline ={currentline.origin,
                    vector<int>{currentline.target[0]+y, currentline.target[1]+x}};
            } else {
                if(mygame->getpiece(currentline.target)->getcolor() !=
                   mygame->getpiece(currentline.origin)->getcolor()) {
                    //meaning that new target is enemy
                    valids.emplace_back(currentline);
                    break;
                } else {
                    //encounting friend piece
                    break;
                }
            }
            
        } else {
            break;
        }
    }

}
void findline(vector<step> &valids, step currentline, int y, int x, game *mygame) {
    while(true) {
        if(inrange(currentline.target)) {
            if(!mygame->getpiece(currentline.target)) {
                //encountering blank spot
                game copy {*(mygame)};
                delete copy.board.at(currentline.target[0]).at(currentline.target[1]);
                copy.board.at(currentline.target[0]).at(currentline.target[1]) = copy.getpiece(currentline.origin);
                copy.board.at(currentline.origin[0]).at(currentline.origin[1]) = nullptr;
                copy.board.at(currentline.target[0]).at(currentline.target[1])->changeposn(currentline.target);
                if((mygame->getpiece(currentline.origin)->getcolor() == Color::white)&&
                   (!copy.whiteisCheck())){
                    valids.emplace_back(currentline);
                }
                if((mygame->getpiece(currentline.origin)->getcolor() == Color::black)&&
                   (!copy.blackisCheck())){
                    valids.emplace_back(currentline);
                }
                currentline ={currentline.origin,
                    vector<int>{currentline.target[0]+y, currentline.target[1]+x}};
            } else {
                if(mygame->getpiece(currentline.target)->getcolor() !=
                   mygame->getpiece(currentline.origin)->getcolor()) {
                    //meaning that new target is enemy
                    game copy {*(mygame)};
                    delete copy.board.at(currentline.target[0]).at(currentline.target[1]);
                    copy.board.at(currentline.target[0]).at(currentline.target[1]) = copy.getpiece(currentline.origin);
                    copy.board.at(currentline.origin[0]).at(currentline.origin[1]) = nullptr;
                    copy.board.at(currentline.target[0]).at(currentline.target[1])->changeposn(currentline.target);
                    if((mygame->getpiece(currentline.origin)->getcolor() == Color::white)&&(!copy.whiteisCheck())){
                        valids.emplace_back(currentline);
                    }
                    if((mygame->getpiece(currentline.origin)->getcolor() == Color::black)&&(!copy.blackisCheck())){
                        valids.emplace_back(currentline);
                    }
                    break;
                } else {
                    //encounting friend piece
                    break;
                }
            }
            
        } else {
            break;
        }
    }
}
bool checkstep_nocheck (step target, game *mygame) {
    if(inrange(target.target)) {
        
        if(!mygame->getpiece(target.target)) {
            
            return true;
        } else {
            //if(!mygame->getpiece(target.origin)){cout <<"bad exe"<<endl;}
            if(mygame->getpiece(target.target)->getcolor() !=
               mygame->getpiece(target.origin)->getcolor()) {
                return true;
            
            } else {
                return false;
            }
            
        }
    }
    return false;
}
bool checkstep (step target, game *mygame) {
    if(inrange(target.target)) {
        
        if(!mygame->getpiece(target.target)) {
            
            game copy {*(mygame)};
            delete copy.board.at(target.target[0]).at(target.target[1]);
            copy.board.at(target.target[0]).at(target.target[1]) = copy.getpiece(target.origin);
            copy.board.at(target.origin[0]).at(target.origin[1]) = nullptr;
            copy.board.at(target.target[0]).at(target.target[1])->changeposn(target.target);
            /*if(mygame->getpiece(target.origin)->getpiece()==Piece::K){
             copy.displayboard();
             }
            cout<<copy.whiteisCheck()<<endl;
            
            cout<<"<<<<<<<<<<"<<endl;*/
            
            if((mygame->getpiece(target.origin)->getcolor()  == Color::white)&&(!copy.whiteisCheck())){
                /*if(mygame->getpiece(target.origin)->getpiece()==Piece::K){
                    copy.displayboard();
                }*/
                return true;
            }
            if((mygame->getpiece(target.origin)->getcolor() == Color::black)&&
               (!copy.blackisCheck())){
                return true;
            }
        } else {
            if(mygame->getpiece(target.target)->getcolor() !=
               (mygame->getpiece(target.origin)->getcolor())) {
                game copy {*(mygame)};
                
                delete copy.board.at(target.target[0]).at(target.target[1]);
                copy.board.at(target.target[0]).at(target.target[1]) = copy.getpiece(target.origin);
                copy.board.at(target.origin[0]).at(target.origin[1]) = nullptr;
                copy.board.at(target.target[0]).at(target.target[1])->changeposn(target.target);
                if((mygame->getpiece(target.origin)->getcolor() == Color::white)&&(!copy.whiteisCheck())){
                    return true;
                }
                if((mygame->getpiece(target.origin)->getcolor() == Color::black)&&(!copy.blackisCheck())){
                    return true;
                }
            } else {
                return false;
            }
            
        }
    }
    return false;
}
