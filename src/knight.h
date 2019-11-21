//
//  knight.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef knight_h
#define knight_h

#include "basicpiece.h"
using namespace std;
class knight: public basicpiece {
public:
    knight(knight &other);
    knight *duplicate()override;
    knight(Color p, vector<int> posn, game *thegame);
    vector<step> validmoves() override;
    bool isvalid(vector<int> target) override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};

#endif /* knight_hpp */
