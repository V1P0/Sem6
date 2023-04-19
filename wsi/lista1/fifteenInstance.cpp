//
// Created by BEAST on 17.04.2023.
//

#include "fifteenInstance.h"
#include <iostream>
using namespace std;


FifteenInstance::FifteenInstance(char board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->board[i][j] = board[i][j];
            if (board[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }
    parent = nullptr;
    g = 0;
    f = 0;
}

FifteenInstance::FifteenInstance(char board[4][4], FifteenInstance* parent) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->board[i][j] = board[i][j];
            if (board[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }
    this->parent = parent;
    g = parent->g + 1;
    f = 0;
}

FifteenInstance::FifteenInstance(const FifteenInstance& other) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->board[i][j] = other.board[i][j];
            if (other.board[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }
    this->parent = other.parent;
    this->g = other.g;
    this->f = other.f;
}

FifteenInstance& FifteenInstance::operator=(const FifteenInstance& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->board[i][j] = other.board[i][j];
                if (other.board[i][j] == 0) {
                    blankX = i;
                    blankY = j;
                }
            }
        }
        this->parent = other.parent;
        this->g = other.g;
        this->f = other.f;
    }
    return *this;
}

FifteenInstance::~FifteenInstance() {
    parent = nullptr;
}

bool FifteenInstance::isGoal() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != (i<<2)+ j+ 1) {
                return false;
            }
        }
    }
    for (int j = 0; j < 3; j++) {
        if (board[3][j] != (3<<2)+ j+ 1) {
            return false;
        }
    }
    return true;
}

bool FifteenInstance::isSolvable() const {
    int inversions = 0;
    char arr[16];
    int k = 0;
    int blankRow = 3 - blankX;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[k++] = board[i][j];
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 16; j++) {
            if (arr[j] && arr[i] && arr[i] > arr[j]) {
                inversions++;
            }
        }
    }
    return (inversions + blankRow) % 2 == 0;
}

vector<FifteenInstance*> FifteenInstance::getChildren() const {
    vector<FifteenInstance*> children;
    signed char shiftx[] = {1, -1, 0, 0};
    signed char shifty[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        if (blankX + shiftx[i] < 0 || blankX + shiftx[i] > 3 || blankY + shifty[i] < 0 || blankY + shifty[i] > 3) {
            continue;
        }
        char newBoard[4][4];
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                newBoard[j][k] = board[j][k];
            }
        }
        newBoard[blankX][blankY] = newBoard[blankX + shiftx[i]][blankY + shifty[i]];
        newBoard[blankX + shiftx[i]][blankY + shifty[i]] = 0;
        auto* child = new FifteenInstance(newBoard, const_cast<FifteenInstance*>(this));
        children.push_back(child);
    }
    return children;
}




