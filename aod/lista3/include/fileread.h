//
// Created by krrer on 11.05.23.
//

#ifndef LAB3_SRC_FILEREAD_H_
#define LAB3_SRC_FILEREAD_H_
#include "graph_utill.h"
#include "algorithms.h"

struct ExperimentData{
  std::string graph_file;
  std::string sources_file;
};

class Filereader {
 public:
  static std::shared_ptr<Graph> readGraph(const std::string &filename);
  static std::shared_ptr<SsSources> readSSfile(const std::string &filename);
  static std::shared_ptr<P2pSsources> readP2Pfile(
      const std::string &filename);
  static void writeP2PResult(const std::string &filename,
                             std::vector<algorithms::dijstra_return_data> results,
                             const ExperimentData& data);
  static void writeSSResult(const std::string &filename,
                                 std::vector<algorithms::dijstra_return_data> results,
                                 const ExperimentData& data) ;
};
#endif //LAB3_SRC_FILEREAD_H_
