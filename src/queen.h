//
//  queen.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef queen_h
#define queen_h

#include "basicpiece.h"
using namespace std;
class queen: public basicpiece {
public:
    queen(queen &other);
    queen *duplicate()override;
    queen(Color p, vector<int> posn, game *thegame);

    vector<step> validmoves() override;
    bool isvalid(vector<int> target) override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};
#endif /* queen_hpp */
