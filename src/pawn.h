//
//  pawn.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef pawn_h
#define pawn_h
#include <string>
#include "basicpiece.h"
using namespace std;
class pawn: public basicpiece {
    bool initial;
    bool initial2;
    string EP;
public:
    pawn *duplicate()override;
    pawn(pawn &other);
    void setEP(string ep);
    pawn(Color player, vector<int> posn, game *thegame);
    void initialize(int moves) override;
    vector<step> validmoves() override;
    bool isvalid(vector<int>target) override;
    bool justinitial2() override;
    void deinitial2() override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};
#endif /* pawn_hpp */
