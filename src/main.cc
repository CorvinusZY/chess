//
//  main.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "king.h"
#include "display.h"
#include "biship.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "computer.h"
#include "step.h"
#include "basicpiece.h"
#include <sstream>
#include <time.h>

using namespace std;

vector<int> cordTrans(string str){
    
    vector<int> cord{0, 0};
    char cmp1 ='a';
    char cmp2 ='1';
    for(int i = 0; i < 8; i++){
        if(str[0] == cmp1){
            cord.at(1) = i;
            break;
        }
        cmp1++;
    }
    for(int i = 0; i < 8; i++){
        if(str[1] == cmp2){
            cord.at(0) = i;
            break;
        }
        cmp2++;
    }
    return cord;
}

Color reverseColor(Color input){
    if (input == Color::black){
        return Color::white;
    }else {
        return Color::black;
    }
}

int diffIdentity(string player){
    if(player == "computer1"){
        return 1;
    }else if (player == "computer2"){
        return 2;
    }else if (player == "computer3"){
        return 3;
    }else if (player == "computer4"){
        return 4;
    }else{
        return 0;
    }
}
int main() {
    
    double duration;
    string line;
    
    string white_player;
    string black_player;
    double whiteScore = 0;
    double blackScore = 0;

    Color currPlayer = Color::black;
    Piece movetype;
    
    game* currgame = nullptr;
    while (getline(cin, line)){
        bool humanVH = false;
        bool humanVC = false;
        bool computerVC = false ;
        int diff1 = 0;
        int diff2 = 0;
        
        istringstream stream;
        //cout<<line<<endl;
        stream.str(line);
        
        
        //cout<<stream.str()<<endl;
        string command;
        stream>>command;
        //cout<<command<<endl;
        if(command == "game"){
            stream >> white_player;
            stream >> black_player;
            // player can be human or computer[1-4]
            if(white_player == "human"){
                if(black_player == "human"){
                    humanVH = true;//HVH
                }else if ((black_player == "computer1")||
                          (black_player == "computer2")||
                          (black_player == "computer3")||
                          (black_player == "computer4")){
                    humanVC = true;//HVC
                } else {
                    goto newloop;
                }
            }else if ((white_player == "computer1")||
                      (white_player == "computer2")||
                      (white_player == "computer3")||
                      (white_player == "computer4")){
                if(black_player == "human"){
                    humanVC = true;//HVC
                }else if ((black_player == "computer1")||
                          (black_player == "computer2")||
                          (black_player == "computer3")||
                          (black_player == "computer4")){
                    computerVC = true;//CVC
                } else {
                    goto newloop;
                }
            } else
            {
                goto newloop;
            }
            ////8:32PM 5.1.5
            
            currgame = new game(humanVH,humanVC,computerVC,diff1,diff2,currPlayer);
            currgame->initial();
            if(currgame->humanVC || currgame->computerVC){
                diff1 = diffIdentity(white_player);
                diff2 = diffIdentity(black_player);
                if(diff1 > 0){
                    currgame->addComputer(1,diff1);
                }
                if(diff2 > 0){
                    currgame->addComputer(2,diff2);
                }
            }
            currgame->displayboard();
            
            if(currgame->humanVC && (black_player != "human")){
                step currstep = currgame->AIMove(2);
                movetype = currgame->getpiece(currstep.origin)->getpiece();
                if((movetype == Piece::P)&&(currstep.target[0] == 0)){
                    currgame->promoteP(currstep.origin, currstep.target, "Q");
                }else{
                    currgame->move(currstep.origin,currstep.target,Color::black);
                }
                //currgame->move(currstep.origin,currstep.target,Color::black);
                //currgame->displayboard();
            }
            if(currgame->computerVC){
                clock_t starttime = clock();
                while (!currgame->isWon()){
                     
                    duration = (clock()-starttime)/(double)CLOCKS_PER_SEC;
                   
                    if(duration >60){
                        cout<<"game last too long"<<endl;
                        cout<<"please try again"<<endl;
                        delete currgame;
                        break;
                    }
                    if(currgame->blackisCheck()) {cout<<"Black is in check"<<endl;}
                    if(currgame->whiteisCheck()) {cout<<"White is in check"<<endl;}
                    if(currgame->isStalemate()) {
                        cout<<"Stalemate!"<<endl;
                        blackScore += 0.5;
                        whiteScore += 0.5;
                        cout <<"whitescore:"<<whiteScore<<endl;
                        cout <<"blackscore:"<<blackScore<<endl;
                        delete currgame;
                        break;
                    }
                    step currstep = currgame->AIMove(2);
                    movetype = currgame->getpiece(currstep.origin)->getpiece();
                    if((movetype == Piece::P)&&(currstep.target[0] == 0)){
                        currgame->promoteP(currstep.origin, currstep.target, "Q");
                    }else{
                        currgame->move(currstep.origin,currstep.target,Color::black);
                    }
                    if(currgame->isWon()){
                        
                        if(currgame->blackisCheckmate()){
                            cout <<"Checkmate! White wins!"<<endl;
                            whiteScore++;
                        }else{
                            cout<<"Checkmate! Black wins!"<<endl;
                            blackScore++;
                        }
                        cout <<"whitescore:"<<whiteScore<<endl;
                        cout <<"blackscore:"<<blackScore<<endl;
                        delete currgame;

                        break;
                    }
                    
                    //currgame->displayboard();
                    if(!currgame->isWon()){
                        if(currgame->blackisCheck()) {cout<<"Black is in check"<<endl;}
                        if(currgame->whiteisCheck()) {cout<<"White is in check"<<endl;}
                        if(currgame->isStalemate()) {
                            cout<<"Stalemate!"<<endl;
                            blackScore += 0.5;
                            whiteScore += 0.5;
                            cout <<"whitescore:"<<whiteScore<<endl;
                            cout <<"blackscore:"<<blackScore<<endl;
                            delete currgame;
                            break;
                        }
                        step currstep = currgame->AIMove(1);
                        movetype = currgame->getpiece(currstep.origin)->getpiece();
                        if((movetype == Piece::P)&&(currstep.target[0] == 7)){
                            currgame->promoteP(currstep.origin, currstep.target, "Q");
                        }else{
                            currgame->move(currstep.origin,currstep.target,Color::white);
                        }
                    }
                    if(currgame->isWon()){
                        
                            if(currgame->blackisCheckmate()){
                                cout <<"Checkmate! White wins!"<<endl;
                                whiteScore++;
                            }else{
                                cout<<"Checkmate! Black wins!"<<endl;
                                blackScore++;
                            }
                        cout <<"whitescore:"<<whiteScore<<endl;
                        cout <<"blackscore:"<<blackScore<<endl;
                        delete currgame;

                        break;
                    }
                }
            }
            
        }
        
        else if (command == "print") {currgame->displayboard();}
        else if ((command == "setup")&&((!currgame)||(!currgame->initialized))){
            Color pieceColor;
            Piece type;
            humanVH = true;
            currgame = new game(humanVH,humanVC,computerVC,diff1,diff2,currPlayer);
            currgame->entersetup();
            /// NOW ALL NULLPTR
            string command1;
            while(cin>>command1){
                if(command1 == "+"){
                    cin >> command1;
                    if(command1 == "K"){
                        type = Piece::K;
                        pieceColor = Color::white;
                    }else if(command1 == "Q"){
                        type = Piece::Q;
                        pieceColor = Color::white;
                    }else if(command1 == "B"){
                        type = Piece::B;
                        pieceColor = Color::white;
                    }else if(command1 == "KN"){
                        type = Piece::KN;
                        pieceColor = Color::white;
                    }else if(command1 == "R"){
                        type = Piece::R;
                        pieceColor = Color::white;
                    }else if(command1 == "P"){
                        type = Piece::P;
                        pieceColor = Color::white;
                    }else if(command1 == "k"){
                        type = Piece::K;
                        pieceColor = Color::black;
                    }else if(command1 == "q"){
                        type = Piece::Q;
                        pieceColor = Color::black;
                    }else if(command1 == "b"){
                        type = Piece::B;
                        pieceColor = Color::black;
                    }else if(command1 == "kn"){
                        type = Piece::KN;
                        pieceColor = Color::black;
                    }else if(command1 == "r"){
                        type = Piece::R;
                        pieceColor = Color::black;
                    }else if(command1 == "p"){
                        type = Piece::P;
                        pieceColor = Color::black;
                    }
                    cin >> command1;
                    vector<int> cord = cordTrans(command1);
                    currgame->setup(cord,type,pieceColor);
                    currgame->displayboard();
                    
                }else if(command1 == "-"){
                    cin >> command1;
                    vector<int> cord = cordTrans(command1);
                    currgame->setup(cord);
                    currgame->displayboard();
                }else if(command1 == "="){
                    cin >> command1;
                    if(command1 == "black"){
                        currgame->setplayer(Color::black);
                        //currPlayer = Color::black;
                    }else{
                        currgame->setplayer(Color::white);
                        //currPlayer = Color::white;
                    }
                    ///////////////need to set currplayer; no public method!!!!!!!!!
                }else if(command1 == "done"){
                    
                    if(currgame->setupdone()){
                    currgame->initial();
                    currgame->displayboard();
                        break;
                    } else {
                        cout<<"Board needs more setup"<<endl;
                    }
                }
            
                
            }
            
        }
        else if((command == "move")&&(currgame->initialized)){
            string command1;
            stream >> command1;
            
            
            //cout<<command1<<endl;
            vector<int> cord = cordTrans(command1);
            string command2;
            stream >> command2;
            
            vector<int> target = cordTrans(command2);
            string command3;
            
            try{
                if(stream>>command3) {
                    currgame->promoteP(cord, target, command3);
                    
                } else {currgame->move(cord,target,currgame->getcurr());}
                //currPlayer = reverseColor(currPlayer);
            }
            catch(string e) {cout <<e<<endl;}
            //cout <<"end move"<<endl;
            //////
            
            //basicpiece *temp = currgame->gettype(Color::white, Piece::K);
            /*if(true) {
                int size = temp->validmoves().size();
                cout <<"size"<<size<<endl;
                for(int i=0; i<size;i++) {
                    cout <<"from"<<temp->validmoves()[i].origin[0]<<temp->validmoves()[i].origin[1];
                    cout<<"to"<<temp->validmoves()[i].target[0]<<temp->validmoves()[i].target[1]<<endl;
                }
            }*/
            
            if(!currgame->humanVH){
                ////////////////AI moves
                if(white_player!="human"){
                    step currstep = currgame->AIMove(1);
                    movetype = currgame->getpiece(currstep.origin)->getpiece();
                    if((movetype == Piece::P)&&(currstep.target[0] == 7)){
                        currgame->promoteP(currstep.origin, currstep.target, "Q");
                    }else{
                        currgame->move(currstep.origin,currstep.target,Color::white);
                    }
                    //currgame->displayboard();
                }else{
                    step currstep = currgame->AIMove(2);
                    movetype = currgame->getpiece(currstep.origin)->getpiece();
                    if((movetype == Piece::P)&&(currstep.target[0] == 0)){
                        currgame->promoteP(currstep.origin, currstep.target, "Q");
                    }else{
                        currgame->move(currstep.origin,currstep.target,Color::black);
                    }
                }
            }
            if(currgame->blackisCheck()) {cout<<"Black is in check"<<endl;}
            if(currgame->whiteisCheck()) {cout<<"White is in check"<<endl;}
            if(currgame->isStalemate()) {
                
                cout<<"Stalemate!"<<endl;
                blackScore += 0.5;
                whiteScore += 0.5;
                cout <<"whitescore:"<<whiteScore<<endl;
                cout <<"blackscore:"<<blackScore<<endl;
                delete currgame;
            }
            if(currgame->isWon()){
                if(currgame->blackisCheckmate()){
                    cout <<"Checkmate! White wins!"<<endl;
                    whiteScore++;
                }else{
                    cout<<"Checkmate! Black wins!"<<endl;
                    blackScore++;
                }
                cout <<"whitescore:"<<whiteScore<<endl;
                cout <<"blackscore:"<<blackScore<<endl;

                delete currgame;
                ///delete game
            }
            
        }else if (command == "resign"){
            if(currgame->getcurr() == Color::white){
                blackScore++;
            }else{
                whiteScore++;
            }
            cout <<"whitescore:"<<whiteScore<<endl;
            cout <<"blackscore:"<<blackScore<<endl;
            delete currgame;
            //currgame = new game(humanVH,humanVC,computerVC,diff1,diff2,currPlayer);
            
        } else if (command == ""){}
        else{
        newloop:

            cout << "invalid command"<<endl;
        }

        //stream.str("");
      
    }
    /////cout score of player;
    return 0;
}
