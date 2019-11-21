//
//  biship.hpp
//  a5
//
//  Created by Corvinus on 2018-03-31.
//  Copyright © 2018 Corvinus. All rights reserved.
//

#ifndef biship_h
#define biship_h

#include "basicpiece.h"
using namespace std;
class biship: public basicpiece {
public:
    biship(biship &other);
    biship *duplicate()override;
    biship(Color p, vector<int> posn, game *thegame);
    bool isvalid(vector<int> target) override;
    vector<step> validmoves() override;
    vector<step> moves() override;
    bool ismovable(vector<int>target) override;
};

#endif /* biship_hpp */
