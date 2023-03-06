#pragma once
#include <iostream>
#include <stdbool.h>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;

bool isSolvable(vector<int> puzzle);

class Heuristic{
public:
    virtual int distance(vector<int> state) = 0;
};

class MisplacedTiles: public Heuristic{
public:
    int distance(vector<int> state);
};

class ManhattanDistance: public Heuristic{
public:
    int distance(vector<int> state);
};

class MDLinearConflict: public Heuristic{
public:
    int distance(vector<int> state);
};

class InvertDistance: public Heuristic{
public:
    int distance(vector<int> state);
};

class WalkingDistance: public Heuristic{
public:
    int distance(vector<int> state);
};

class Node{
public:
    vector<int> state;
    int f, g;
    int blank;
    Node* previous;
    Node(vector<int> instance, Heuristic* heuristic){
        for(int i = 0; i<instance.size(); i++){
            if(instance[i]==0){
                blank=i;
            }
            state.push_back(instance[i]);
        }
        g = 0;
        f = heuristic->distance(state);
        previous = nullptr;
    }
    Node(vector<int> instance, Heuristic* heuristic, Node* parent, int b){
        for(int i = 0; i<instance.size(); i++){
            state.push_back(instance[i]);
        }
        g = parent->g + 1;
        blank = b;
        f = g + heuristic->distance(state);
        previous = parent;
    }
    ~Node(){
        if(previous != nullptr){
            delete(previous);
        }
    }
    bool isTarget(){
        for(int i = 0; i<15; i++){
            if(state[i]!=i+1){
                return false;
            }
        }
        return true;
    }
    vector<Node*> expand(Heuristic* heuristic){
        int shiftx[] = {1,-1,0,0};
        int shifty[] = {0,0,1,-1};
        vector<Node*> neighbours;
        for(int i = 0; i<4; i++){
            int x = blank%4;
            int y = blank/4;
            int nx = x+shiftx[i];
            int ny = y+shifty[i];
            if(nx<0||nx>3||ny<0||ny>3){
                continue;
            }
            int new_blank = 4*ny+nx;
            vector<int> new_state(state);
            if(new_blank == blank){
                cout << "AAAAAAAAAA";
            }
            swap(new_state[blank], new_state[new_blank]);
            Node* new_node = new Node(new_state, heuristic, this, new_blank);
            neighbours.push_back(new_node);
        }
        return neighbours;
    }
};

Node* solve(vector<int> state, Heuristic* h);