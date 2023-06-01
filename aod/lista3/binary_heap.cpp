#include <iostream>
#include "include/fileread.h"
#include "include/algorithms.h"
#include <chrono>
int main(int argc, char *argv[]) {
  std::string input, output, sources;
  std::shared_ptr<SsSources> ss_sources{};
  std::shared_ptr<P2pSsources> p2p_sources{};
  bool is_p2p = false;
  bool is_ss = false;
  for (int i = 1; i < argc; i++) {
    auto x = argv[i];
    if (strcmp(argv[i], "-d") == 0) {
      i += 1;
      input = std::string(argv[i]);
      continue;
    }
    if (strcmp(argv[i], "-ss") == 0) {
      is_ss = true;
      sources = argv[++i];
      continue;
    }
    if (strcmp(argv[i], "-p2p") == 0) {
      is_p2p = true;
      sources = argv[++i];
      continue;
    }
    if (strcmp(argv[i], "-oss") == 0 || strcmp(argv[i], "-op2p") == 0) {

      output = argv[++i];
      output  += "_bh";
      continue;
    }
  }

  auto graph = Filereader::readGraph(input);
  std::vector<algorithms::dijstra_return_data> results;
  if (is_ss) {
    ss_sources = Filereader::readSSfile(sources);
    for (const auto &source : ss_sources->verticies) {
      auto start = std::chrono::high_resolution_clock::now();

      //      std::unique_ptr<algorithms::PriorityQueue> pq = std::make_unique<algorithms::DialPriorityQueue>(graph->max_edge);
      //      std::unique_ptr<algorithms::PriorityQueue> dpq = std::make_unique<algorithms::StdPriorityQueue>();
//      std::unique_ptr<algorithms::PriorityQueue>
//          rhpq = std::make_unique<algorithms::RadixHeap>(graph->max_edge, graph->getSize());
            std::unique_ptr<algorithms::PriorityQueue> bh = std::make_unique<algorithms::BinaryHeap>(graph->getSize());

      auto result = algorithms::runDijsktra(*graph, source, 0, bh);
      auto stop = std::chrono::high_resolution_clock::now();
      result.time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0 ;
      results.push_back(result);
      std::cout << "source: " + std::to_string(source) + " " << result.toString() << std::endl;
    }
    Filereader::writeSSResult(output, results, {input, sources});

  } else if (is_p2p) {
    p2p_sources = Filereader::readP2Pfile(sources);
    for (const auto &[source, dest] : p2p_sources->search_pairs) {
      std::unique_ptr<algorithms::PriorityQueue> bh = std::make_unique<algorithms::BinaryHeap>(graph->getSize());

      auto result = algorithms::runDijsktra(*graph, source, dest, bh);
      results.push_back(result);
      std::cout
          << "source: " + std::to_string(source) + " dest: " + std::to_string(dest) + " distance: "
              + std::to_string(result.path) + " " << result.toString() << std::endl;
    }
    Filereader::writeP2PResult(output, results, {input, sources});
  } else {
    std::cerr << "Sources not declared\n";
    return -1;
  }

  std::cout << "Finished" << std::endl;
  return 0;
}
