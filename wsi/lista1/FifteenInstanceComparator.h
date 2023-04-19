//
// Created by BEAST on 17.04.2023.
//

#ifndef PUZZLE15SOLVER_FIFTEENINSTANCECOMPARATOR_H
#define PUZZLE15SOLVER_FIFTEENINSTANCECOMPARATOR_H


#include "fifteenInstance.h"

class FifteenInstanceComparator {
public:
    bool operator()(FifteenInstance* a, FifteenInstance* b) {
        return a->f > b->f;
    }
};


#endif //PUZZLE15SOLVER_FIFTEENINSTANCECOMPARATOR_H
