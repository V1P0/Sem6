//
// Created by BEAST on 18.04.2023.
//

#ifndef PUZZLE15SOLVER_FIFTEENSOLVER_H
#define PUZZLE15SOLVER_FIFTEENSOLVER_H
#include <array>
#include <vector>
#include "heuristics.h"
#include "fifteenInstance.h"
using namespace std;

vector<array<array<char, 4>, 4>> AStar(FifteenInstance* start,  Heuristic* heuristic, long long int& counter);

#endif //PUZZLE15SOLVER_FIFTEENSOLVER_H
