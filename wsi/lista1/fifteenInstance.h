//
// Created by BEAST on 17.04.2023.
//

#ifndef PUZZLE15SOLVER_FIFTEENINSTANCE_H
#define PUZZLE15SOLVER_FIFTEENINSTANCE_H
#include <vector>
#include <string>
#include <array>

class FifteenInstance {
    char blankX;
    char blankY;

public:
    int f, g;
    explicit FifteenInstance(char board[4][4]);
    FifteenInstance(char board[4][4], FifteenInstance* parent);
    FifteenInstance(const FifteenInstance& other);
    FifteenInstance& operator=(const FifteenInstance& other);
    ~FifteenInstance();

    [[nodiscard]] bool isGoal() const;
    [[nodiscard]] bool isSolvable() const;
    [[nodiscard]] std::vector<FifteenInstance*> getChildren() const;


    std::array<std::array<char, 4>, 4> board{};
    FifteenInstance* parent;
};


#endif //PUZZLE15SOLVER_FIFTEENINSTANCE_H
