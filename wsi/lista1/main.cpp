#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "FifteenSolver.h"

using namespace std;



int main() {

    Heuristic* wd = new WalkingDistance();
    Heuristic* md = new ManhattanDistance();

    for(int x = 0; x< 1; x++){
        char board[4][4];
        vector<char> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
        //shuffle
        std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
        shuffle(input.begin(), input.end(), gen);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                board[i][j] = input[i*4+j];
            }
        }
        auto* instance = new FifteenInstance(board);
        while(!instance->isSolvable()){
            shuffle(input.begin(), input.end(), gen);
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    board[i][j] = input[i*4+j];
                }
            }
            instance = new FifteenInstance(board);
        }
        long long int countWD = 0;
        long long int countMD = 0;
        vector<array<array<char, 4>, 4>> pathWD = AStar(instance, wd, countWD);
        cout << pathWD.size()-1 << "," << countWD << "," ;
        instance = new FifteenInstance(board);
        vector<array<array<char, 4>, 4>> pathMD = AStar(instance, md, countMD);
        cout << countMD << endl;
    }
    return 0;
}
