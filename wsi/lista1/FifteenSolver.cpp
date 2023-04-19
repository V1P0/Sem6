//
// Created by BEAST on 18.04.2023.
//

#include "FifteenInstanceComparator.h"
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include "FifteenSolver.h"
#include <iostream>



using namespace std;

struct CharArrayComparator {
    bool operator()(const std::array<std::array<char, 4>, 4>& a, const std::array<std::array<char, 4>, 4>& b) const {
        // Compare each element of the arrays
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (a[i][j] != b[i][j]) {
                    return a[i][j] < b[i][j];
                }
            }
        }
        // The arrays are equal
        return false;
    }
};


vector<array<array<char, 4>, 4>> AStar(FifteenInstance* start,  Heuristic* heuristic, long long int& counter) {
    priority_queue<FifteenInstance*, vector<FifteenInstance*>, FifteenInstanceComparator> openSet;
    map<array<array<char, 4>, 4>, FifteenInstance*, CharArrayComparator> closedSet;
    openSet.push(start);
    counter = 0;
    vector<array<array<char, 4>, 4>> path;
    while (!openSet.empty()) {
        FifteenInstance* current = openSet.top();
        counter++;
        if(current->isGoal()) {
            while (current != nullptr) {
                path.push_back(current->board);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            break;
        }
        closedSet[current->board] = current;
        openSet.pop();
        vector<FifteenInstance*> children = current->getChildren();
        for (auto & i : children) {
            if (closedSet.find(i->board) != closedSet.end()) {
                if(i->g < closedSet[i->board]->g){
                    closedSet[i->board]->parent = i->parent;
                    closedSet[i->board]->g = i->g;
                    delete i;
                }
                continue;


            }
            i->f = i->g + heuristic->distance(i->board);
            openSet.push(i);
        }

    }
    //iterate over the open set and delete all the instances
    while (!openSet.empty()) {
        FifteenInstance* current = openSet.top();
        openSet.pop();
        delete current;
    }
    //iterate over the closed set and delete all the instances
    for (auto & i : closedSet) {
        delete i.second;
    }

    return path;

}