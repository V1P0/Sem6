//
// Created by BEAST on 17.04.2023.
//

#ifndef PUZZLE15SOLVER_HEURISTICS_H
#define PUZZLE15SOLVER_HEURISTICS_H
#include <array>

class Heuristic{
public:
    virtual int distance(std::array<std::array<char, 4>, 4> state) = 0;
};

class ManhattanDistance : public Heuristic{
public:
    int distance(std::array<std::array<char, 4>, 4> state) override;
};

class LinearConflict : public Heuristic{
public:
    int distance(std::array<std::array<char, 4>, 4> state) override;
};

class WalkingDistance : public Heuristic{
    int BOARD_WIDTH = 4;
    int BOARD_SIZE = 16;
    int WDTBL_SIZE = 24964;
    unsigned long long int WDPTN[24964];
    short WDLNK[24964][2][4];
    char WDTBL[24964];
    char IDTBL[106];
public:
    WalkingDistance();
    int distance(std::array<std::array<char, 4>, 4> state) override;
};


#endif //PUZZLE15SOLVER_HEURISTICS_H
