//
//  king.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef king_h
#define king_h
#include "basicpiece.h"
using namespace std;


class king: public basicpiece{
    bool initial;
public:
    king(king &other);
    king *duplicate()override;
    bool isinitial() override;
    void initialize(int moves) override;
    king(Color p, vector<int> posn, game *thegame);
    vector<step> validmoves() override;
    bool isvalid(vector<int> target) override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};
#endif /* king_hpp */
