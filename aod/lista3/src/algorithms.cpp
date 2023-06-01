//
// Created by krrer on 11.05.23.
//

#include "../include/algorithms.h"
#include "../include/graph_utill.h"

namespace algorithms {

dijstra_return_data runDijsktra(Graph graph, size_t source, size_t goal, std::unique_ptr<
    PriorityQueue> &container) {
  std::unordered_map<size_t, int> explored;
  std::vector<bool> visited(graph.verticies.size(), false);
  explored.reserve(graph.getSize());
  container->insert({source, 0});
  visited[source] = true;

  dijstra_return_data data =
      {.verticies = 0, .edges = 0, .lowest_cost = INT32_MAX, .highest_cost = INT32_MIN, .time = 0.0f, .source = source, .dest = goal};
  while (!container->empty()) {
    auto [vert, dist] = container->pop();
    if (explored.contains(vert)) continue;
//    std::cout << std::to_string(vert) + " " + std::to_string(dist) << "\n";
    data.verticies++;

    explored.insert({vert, dist});
    if (vert == goal) {
      data.path = dist;
      return data;
    }

    for (const auto &[neighbour, weight] : graph.verticies[vert]) {
      data.edges++;
      data.lowest_cost = std::min(data.lowest_cost, weight);
      data.highest_cost = std::max(data.highest_cost, weight);
      if (!visited[neighbour]) {
        container->insert({neighbour, dist + weight});
        visited[neighbour] = true;
        continue;
      }
      if (!explored.contains(neighbour)) {
        container->decrease_key({neighbour, dist + weight});
        continue;
      }
    }
  }
  return data;
};

}