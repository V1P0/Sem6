//
// Created by krrer on 07.03.23.
//

#ifndef LAB1__GRAPH_H_
#define LAB1__GRAPH_H_

#include <array>
#include <list>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
typedef std::vector<std::list<std::pair<size_t,int>>> graph_edges;

class Graph{
  const size_t verticies_size;
  bool isDirected;


 public:
  int max_edge;
  int min_edge;
  graph_edges verticies;
  Graph(size_t verticies_size, bool isDirected);
  void addEdge(size_t source, size_t dest, int cost);
  size_t getSize() const;
  graph_edges transpose() const;
};

struct SsSources{
  std::vector<size_t> verticies;
};

struct P2pSsources{
  std::vector<std::pair<size_t,size_t>> search_pairs;
};

std::shared_ptr<Graph> readGraphFromFile(std::string filename);


#endif //LAB1__GRAPH_H_
