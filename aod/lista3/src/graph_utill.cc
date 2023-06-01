//
// Created by krrer on 07.03.23.
//

#include "../include/graph_utill.h"
Graph::Graph(size_t verticies_size, bool isDirected) :
    verticies_size(verticies_size),
    verticies(verticies_size+1),
    isDirected(isDirected),
    max_edge(INT32_MIN),
    min_edge(INT32_MAX){}

void Graph::addEdge(size_t source, size_t dest, int cost) {
  verticies[source].emplace_back(dest, cost);
  max_edge = std::max(max_edge,cost);
  min_edge = std::min(min_edge,cost);
  if(!isDirected){
    verticies[dest].emplace_back(source,cost);
  }
}
size_t Graph::getSize() const {
  return verticies_size;
}
graph_edges Graph::transpose() const {
  graph_edges transposed_graph(verticies.size());
  for (int i = 1; i < getSize()+1; i++) {
    for (const auto & [vert,weight] : verticies[i]) {
        transposed_graph[vert].emplace_back(i,weight);
    }
  }
  return transposed_graph;
}

std::shared_ptr<Graph> readGraphFromFile(std::string filename){
  size_t number_of_verticies;
  size_t number_of_edges;
  bool isDirected;
  std::string buffer;

  std::ifstream graphFile;
  graphFile.open(filename);
  if(!graphFile.is_open()){
    std::cout << "Couldn't open file " + filename + "\n";
    return nullptr;
  }
  getline(graphFile,buffer);
  auto special_char_pos = std::find(buffer.cbegin(), buffer.cend(), '\r');
  if(special_char_pos != buffer.cend()) buffer.erase(special_char_pos);
  if(buffer == "D"){
    isDirected = true;
  } else{
    isDirected = false;
  }
  getline(graphFile,buffer);
  number_of_verticies = std::stoi(buffer);
  getline(graphFile,buffer);
  number_of_edges = std::stoi(buffer);

  std::shared_ptr<Graph> graph = std::make_shared<Graph>(number_of_verticies,isDirected);
  for(size_t i = 0; i < number_of_edges; i++){
    getline(graphFile,buffer);
    std::vector<std::string> words;
    boost::split(words,buffer, boost::is_any_of(" "));
    graph->addEdge(std::stoi(words[0]), std::stoi(words[1]), 1);
  }
  graphFile.close();
  return graph;
}