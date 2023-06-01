//
// Created by krrer on 11.05.23.
//

#include "../include/fileread.h"
std::shared_ptr<Graph> Filereader::readGraph(const std::string &filename) {
  size_t number_of_verticies;
  size_t number_of_edges;
  std::string buffer;
  std::ifstream graphFile;
  graphFile.open(filename);
  std::shared_ptr<Graph> graph;
  if (!graphFile.is_open()) {
    std::cout << "Couldn't open file " + filename + "\n";
    return nullptr;
  }
  while (!graphFile.eof()) {
    getline(graphFile, buffer);
    switch (buffer[0]) {
      case 'c' : {
        break;
      }
      case 'p' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 4);
        assert(words[1] == "sp");
        number_of_verticies = std::stoi(words[2]) + 1;
        number_of_edges = std::stoi(words[3]);
        graph = std::make_shared<Graph>(number_of_verticies, true);
        break;
      }
      case 'a' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 4);
        graph->addEdge(std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]));
        break;
      }
      default: {
        if (buffer.empty()) continue;
        std::cerr << "Could not parse line:" + buffer;
        return {};
      }
    }
  }

  return graph;
}
std::shared_ptr<SsSources> Filereader::readSSfile(const std::string &filename) {
  auto sources = std::make_shared<SsSources>();
  int size;
  std::string buffer;
  std::ifstream graphFile;
  graphFile.open(filename);
  if (!graphFile.is_open()) {
    std::cout << "Couldn't open file " + filename + "\n";
    return nullptr;
  }
  while (!graphFile.eof()) {
    getline(graphFile, buffer);
    switch (buffer[0]) {
      case 'c' : {
        break;
      }
      case 'p' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 5);
        assert(words[2] == "sp");
        assert(words[3] == "ss");
        size = std::stoi(words[4]);
        break;
      }
      case 's' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 2);
        sources->verticies.push_back(std::stoi(words[1]));
        size--;
        break;
      }
      default: {
        if (buffer.empty()) continue;
        std::cerr << "Could not parse line:" + buffer;
        return {};
      }
    }
  }
  assert(size == 0);
  return sources;
}
std::shared_ptr<P2pSsources> Filereader::readP2Pfile(const std::string &filename) {
  auto sources = std::make_shared<P2pSsources>();
  int size;
  std::string buffer;
  std::ifstream graphFile;
  graphFile.open(filename);
  if (!graphFile.is_open()) {
    std::cout << "Couldn't open file " + filename + "\n";
    return nullptr;
  }
  while (!graphFile.eof()) {
    getline(graphFile, buffer);
    switch (buffer[0]) {
      case 'c' : {
        break;
      }
      case 'p' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 5);
        assert(words[2] == "sp");
        assert(words[3] == "p2p");
        size = std::stoi(words[4]);
        break;
      }
      case 'q' : {
        std::vector<std::string> words;
        boost::split(words, buffer, boost::is_any_of(" "));
        assert(words.size() == 3);
        sources->search_pairs.emplace_back(std::stoi(words[1]), std::stoi(words[2]));
        size--;
        break;
      }
      default: {
        if (buffer.empty()) continue;
        std::cerr << "Could not parse line:" + buffer;
        return {};
      }
    }
  }
  assert(size == 0);
  return sources;
}
void Filereader::writeP2PResult(const std::string &filename,
                                std::vector<algorithms::dijstra_return_data> results,
                                const ExperimentData& data) {
  std::ofstream opFile;
  opFile.open(filename);
  if (!opFile.is_open()) {
    std::cout << "Couldn't open file " + filename + "\n";
    return;
  }
  auto experiment_desc = "f " + data.graph_file + " " + data.sources_file + "\n";
  opFile << experiment_desc;
  auto graph_data = "g " + std::to_string(results.front().verticies) + " "
      + std::to_string(results.front().edges) + " "
      + std::to_string(results.front().lowest_cost) + " "
      + std::to_string(results.front().highest_cost) + "\n";
  opFile << graph_data;
  for (const auto &result : results) {
    auto result_line = "d " + std::to_string(result.source) + " "
        + std::to_string(result.dest) + " "
        + std::to_string(result.path) + "\n";
    opFile << result_line;
  }
  opFile.close();
}

void Filereader::writeSSResult(const std::string &filename,
                                std::vector<algorithms::dijstra_return_data> results,
                                const ExperimentData& data) {
  std::ofstream opFile;
  opFile.open(filename);
  if (!opFile.is_open()) {
    std::cout << "Couldn't open file " + filename + "\n";
    return;
  }
  auto experiment_desc = "f " + data.graph_file + " " + data.sources_file + "\n";
  opFile << experiment_desc;
  auto graph_data = "g " + std::to_string(results.front().verticies) + " "
      + std::to_string(results.front().edges) + " "
      + std::to_string(results.front().lowest_cost) + " "
      + std::to_string(results.front().highest_cost) + "\n";
  double time = 0.0;
  opFile << graph_data;
  for (const auto &result : results) {
    time += result.time;
  }
  time /= (double)results.size();
  opFile << "t " + std::to_string(time) << std::endl;
  opFile.close();
}