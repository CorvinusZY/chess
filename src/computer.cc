//
//  computer.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include <stdlib.h>
#include <time.h>
#include "computer.h"
#include "game.h"
#include "basicpiece.h"




computer::computer(int level, game* currgame)
:level(level),currgame(currgame){}

int computer::smart(){
    return this->level;
}
bool computer::isCap(int x, int y, game* passing){
    basicpiece *currpiece = passing->board[x][y];
    Color currColor = currpiece->getcolor();
    //Piece type = currpiece->getpiece();
    Color opColor;
    if(currColor == Color::black){
        opColor = Color::white;
    }else{
        opColor = Color::black;
    }
    
    for (int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            basicpiece *curr = passing->board.at(i).at(j);
            if(curr) {//for non-nullptr pieces
                if(curr->getcolor() == opColor) {
                    if(curr->ismovable(currpiece->getposn())) return true;
                }
            }
        }
    }
    return false;
}


computer::~computer() {
}
step computer::bestMove()

{
    srand(unsigned(time(NULL)));
    Color currplayer = currgame->getcurr();
    int size;
    if(this->smart() == 1){
        if(currplayer == Color::black){
            size = currgame->blackvalids().size();
            return currgame->blackvalids()[rand() % size];
        }else{
            
            size = currgame->whitevalids().size();
            int random =rand() % size;
            //cout<<"valid size"<<size<<"random number:"<<random<<endl;
            return currgame->whitevalids()[rand() % size];
        }
    }else if(this->smart()== 2){
        int lastcap = -1;
        vector<step> tempsteps{};
        if(currplayer == Color::black){
            tempsteps = currgame->blackvalids();
        }else{
            tempsteps = currgame->whitevalids();
        }
        int size = tempsteps.size();
        
        
        for (int i = 0; i < size; i++){
            //game temp = *currgame;
            ////////assignment ctor
            //temp.move(tempsteps[i].origin,tempsteps[i].target,Color::black);
            game copy {*(currgame)};
            delete copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]);
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]) = copy.getpiece(tempsteps[i].origin);
            copy.board.at(tempsteps[i].origin[0]).at(tempsteps[i].origin[1]) = nullptr;
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1])->changeposn(tempsteps[i].target);
            
            if((currplayer == Color::black)&&(copy.whiteisCheck())){
                ////free temp??? TEMP is in STACK
                return tempsteps[i];
            }else if((currplayer == Color::white)&&(copy.blackisCheck())){
                return tempsteps[i];
            }else if(currgame->board[tempsteps[i].target[0]][tempsteps[i].target[1]]){
                lastcap = i;
            }
        }
        if (lastcap < 0){
            return tempsteps[rand() % size];
        } else {
            return tempsteps[lastcap];
        }
        
    }else if(this->smart()== 3){
        int doublecap = -1;
        int lastnoncap = -1;
        int lastsave = -1;
        int lastcap = -2;
        vector<step> tempsteps{};
        
        if(currplayer == Color::black){
            tempsteps = currgame->blackvalids();
        }else{
            tempsteps = currgame->whitevalids();
        }
        int size = tempsteps.size();
        
        vector<step> noncapsteps{};
        int noncapsize = 0;
        
        for (int i = 0; i < size; i++){
            
            //game temp = *currgame;
            ////////assignment ctor
            //temp.move(tempsteps[i].origin,tempsteps[i].target,Color::black);
            game copy {*(currgame)};
            delete copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]);
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]) = copy.getpiece(tempsteps[i].origin);
            copy.board.at(tempsteps[i].origin[0]).at(tempsteps[i].origin[1]) = nullptr;
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1])->changeposn(tempsteps[i].target);
            
            
            if((currplayer == Color::black)&&(copy.whiteisCheck())){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    return tempsteps[i];
                }
            }else if((currplayer == Color::white)&&(copy.blackisCheck())){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    return tempsteps[i];
                }
            }else if (isCap(tempsteps[i].origin[0], tempsteps[i].origin[1],currgame)){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    lastsave = i;
                }
            }else if(currgame->board[tempsteps[i].target[0]][tempsteps[i].target[1]]){
                lastcap = i;
            }
            noncapsteps.emplace_back(tempsteps[i]);
            noncapsize++;
            
            if (lastcap == lastsave){doublecap = lastcap;}
        }
        
        
        if(doublecap > -1){
            return tempsteps[doublecap];
        }
        if (lastsave > -1){
            return tempsteps[lastsave];
        }else if(lastcap > -1) {
            return tempsteps[lastcap];
        }else if(noncapsize > 0){
            return noncapsteps[rand() % noncapsize];
        }else{
            return tempsteps[rand() % size];
        }
        
    }else if(this->smart()== 4){
        int doublecap = -1;
        int lastnoncap = -1;
        int lastsave = -1;
        int lastcap = -2;
        vector<step> tempsteps{};
        
        if(currplayer == Color::black){
            tempsteps = currgame->blackvalids();
        }else{
            tempsteps = currgame->whitevalids();
        }
        int size = tempsteps.size();
        
        vector<step> noncapsteps{};
        int noncapsize = 0;
        
        for (int i = 0; i < size; i++){
            
            //game temp = *currgame;
            ////////assignment ctor
            //temp.move(tempsteps[i].origin,tempsteps[i].target,Color::black);
            game copy {*(currgame)};
            delete copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]);
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1]) = copy.getpiece(tempsteps[i].origin);
            copy.board.at(tempsteps[i].origin[0]).at(tempsteps[i].origin[1]) = nullptr;
            copy.board.at(tempsteps[i].target[0]).at(tempsteps[i].target[1])->changeposn(tempsteps[i].target);
            
            if ((currplayer == Color::black)&&(copy.getpiece(tempsteps[i].target)->getpiece() == Piece::P)){
                if(tempsteps[i].target[0] == 0){return tempsteps[i];}
            }else if ((currplayer == Color::white)&&(copy.getpiece(tempsteps[i].target)->getpiece() == Piece::P)){
                if(tempsteps[i].target[0] == 7){return tempsteps[i];}
            }
            
            if((currplayer == Color::black)&&(copy.whiteisCheck())){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    return tempsteps[i];
                }
            }else if((currplayer == Color::white)&&(copy.blackisCheck())){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    return tempsteps[i];
                }
            }else if(isCap(tempsteps[i].origin[0], tempsteps[i].origin[1],currgame)){
                if(!isCap(tempsteps[i].target[0], tempsteps[i].target[1],&copy)){
                    lastsave = i;
                }
            }else if(currgame->board[tempsteps[i].target[0]][tempsteps[i].target[1]]){
                lastcap = i;
            }
            noncapsteps.emplace_back(tempsteps[i]);
            noncapsize++;
            
            if (lastcap == lastsave){doublecap = lastcap;}
        }
        
        
        if(doublecap > -1){
            return tempsteps[doublecap];
        }
        if (lastsave > -1){
            return tempsteps[lastsave];
        }else if(lastcap > -1) {
            return tempsteps[lastcap];
        }else if(noncapsize > 0){
            return noncapsteps[rand() % noncapsize];
        }else{
            return tempsteps[rand() % size];
        }
        
    }
    step tempor;
    return tempor;
}

