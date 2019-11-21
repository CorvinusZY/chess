//
//  computer.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef computer_h
#define computer_h
#include "step.h"

class game;
class computer {
    int level;
    game* currgame;
public:
    ~computer();
    computer(int level, game *currgame);///ctor;
    int smart();
    step bestMove();
    bool isCap(int x, int y, game* passing);
};
#endif /* computer_hpp */
