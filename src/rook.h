//
//  rook.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef rook_h
#define rook_h

#include "basicpiece.h"
using namespace std;
class rook: public basicpiece {
    bool initial;
public:
    rook(rook &other);
    rook *duplicate()override;
    void initialize(int moves) override;
    bool isinitial() override;
    rook(Color p, vector<int> posn, game *thegame);
    vector<step> validmoves() override;
    bool isvalid(vector<int>target) override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};
#endif /* rook_hpp */
