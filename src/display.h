//
//  display.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef display_h
#define display_h

#include <vector>

//#include "window.h"
using namespace std;
class game;
class Xwindow;
class display {
    Xwindow* mywindow;
    game *mygame;
public:
    ~display();
    display(game *thegame);
    //void windowplay();
    void charplay();
};
#endif /* display_hpp */
