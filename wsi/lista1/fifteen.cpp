#include "fifteen.hpp"
#include <iostream>
using namespace std;

int getInvCount(vector<int> arr)
{
    int inv_count = 0;
    for (int i = 0; i < 4 * 4 - 1; i++)
    {
        for (int j = i + 1; j < 4 * 4; j++)
        {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}


bool isSolvable(vector<int> puzzle){
    int invCount = getInvCount(puzzle);

    return !(invCount & 1);

}

int MisplacedTiles::distance(vector<int> state){
    int m = 0;
    for(int i = 0; i<15; i++){
        if(state[i]!=i+1){
            m++;
        }
    }
    if(state[15]!=0){
        m++;
    }
    return m;
}

int ManhattanDistance::distance(vector<int> state){
    int m = 0;
    for(int y = 0; y<4; y++){
        for(int x = 0; x<4; x++){
            if(state[4*y+x]==0) continue;
            int targetX = (state[4*y+x]-1)%4;
            int targetY = (state[4*y+x]-1)/4;
            m+=abs(x-targetX)+abs(y-targetY);
        }
    }
    return m;
}

int MDLinearConflict::distance(vector<int> state){
    int m = 0;
    for(int i = 0; i<16; i++){
        if(state[i]==0){
            m+=(15-i)&0b11+((15-i)>>2);
        }else{
        m+=abs((state[i]-(i+1))&0b11)+abs((state[i]-(i+1))>>2);
        }
    }
    for(int i = 0; i<4; i++){
        for(int j = i; j<16; j+=4){
            if(state[j]!=j+1 && state[j]%4==i+1){
                m+=2;
            }
        }
    }
    for(int i = 0; i<16; i+=4){
        for(int j = i; j<i+4; j++){
            if(state[j]!=j+1 && state[j]%4==j+1){
                m+=2;
            }
        }
    }
    return m;
}

int InvertDistance::distance(vector<int> state){


	int inv = 0;
	for(int i = 0; i < 16; i++ ){
		if( state[i] != 0 ){
			for(int j = 0; j < i; j++ ){
				if( state[i] < state[j] ){
					inv++;;
				}
			}
		}
	}
	int vertical = inv/3 + inv%3;
    int unpacked[16];
	int idx = 0;
	for(int i = 0; i < 4; i++ ){
		for(int j = 0; j < 4; j++ ){
			unpacked[idx] = j*4 + i;
			idx++;
		}
	}

	inv = 0;
	for(int i = 0; i <4; i++ ){
		for(int j = 0; j < 4; j++ ){
			int val = state[4*i+j] - 1;
			if( val != -1 ){
				idx = 0;
				for(int k = 0; k<16; k++){
					if( unpacked[k] == val ){
						idx = k;
						break;
					}
				}
				inv += abs(idx - (j*4 + i));
			}
		}
	}
	int horizontal = inv/3 + inv%3;

	return vertical + horizontal;
}

int WalkingDistance::distance(vector<int> state){
    //TODO
    return 0;
}

class Compare
{
public:
    bool operator() (Node* lhs, Node* rhs)
    {
        return lhs->f>rhs->f;
    }
};

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

Node* solve(vector<int> state, Heuristic* h){
    unordered_map<vector<int>, Node*, VectorHasher> visited;
    Node* start = new Node(state, h);
    priority_queue<Node*, vector<Node*>,Compare> queue;
    queue.push(start);
    while(!queue.empty()){
        Node* q = queue.top();
        queue.pop();
        if(q->isTarget()){
            return q;
        }
        visited[q->state] = q;
        vector<Node*> neighbours = q->expand(h);
        for(int i = 0; i<neighbours.size(); i++){
            if(neighbours[i]->isTarget()){
                return neighbours[i];
            }
            if(visited.find(neighbours[i]->state)==visited.end()){
                queue.push(neighbours[i]);
            }else{
                Node* already_visited = visited[neighbours[i]->state];
                if(already_visited->g>neighbours[i]->g){
                    visited[neighbours[i]->state] = neighbours[i];
                    queue.push(neighbours[i]);
                }
            }
        }
    }
    return nullptr;
}

int main(){
    Heuristic* id = new InvertDistance();
    Heuristic* md = new ManhattanDistance();

    //vector<int> state{0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    vector<int> state{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    cout << md->distance(state) << endl;
    cout << id->distance(state) << endl;
    return 0;
}