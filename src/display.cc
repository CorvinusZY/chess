
//
//  display.cpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#include "display.h"
#include "game.h"
#include "window.h"

display::display(game *thegame) {
    mygame = thegame;
    mywindow = new Xwindow(800, 800);
}

display::~display(){delete mywindow;}

void display::charplay() {
    int linecount = 8;
    for(int i=7;i>=0;i--) {
        cout<<linecount<<" ";
        linecount--;
        for(int j=0; j<8; j++) {
            if(!mygame->board.at(i).at(j)){
                if((i+j)%2 == 1) {cout <<' ';}
                else {cout << '-';}
            }
            else {
                if(mygame->board.at(i).at(j)->getcolor() == Color::black){
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::K) {cout<<'k';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::Q) {cout<<'q';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::KN) {cout<<'n';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::R) {cout<<'r';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::P) {cout<<'p';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::B) {cout<<'b';}
                } else {
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::K) {cout<<'K';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::Q) {cout<<'Q';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::KN) {cout<<'N';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::R) {cout<<'R';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::P) {cout<<'P';}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::B) {cout<<'B';}
                }
            }
        }
        cout <<endl;
    }
    cout<<endl<<"  abcdefgh"<<endl;
    for(int i=7;i>=0;i--) {
        for(int j=0; j<8; j++){
            int color = 0;
            if((i+j)%2 == 1) {color = 0;}
            else {color = 6;}
            mywindow->fillRectangle(j*100, (7-i)*100, 100, 100, color);
            
            if(mygame->board.at(i).at(j) != nullptr){
                //mywindow->drawBigString(j*100+30, (7-i)*100+50, to_string(i)+to_string(j));
                
                if(mygame->board.at(i).at(j)->getcolor() == Color::black){
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::K) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:king");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::Q) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:queen");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::KN) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:knight");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::R) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:rook");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::P) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:pawn");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::B) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "B:bishop");;}
                } else {
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::K) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:king");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::Q) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:queen");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::KN) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:knight");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::R) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:rook");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::P) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:pawn");}
                    if(mygame->board.at(i).at(j)->getpiece() == Piece::B) {mywindow->drawBigString(j*100+30, (7-i)*100+50, "W:bishop");}
                }
            }
        }
    }
}
