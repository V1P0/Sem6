//
// Created by krrer on 11.05.23.
//

#ifndef LAB3_SRC_ALGORITHMS_H_
#define LAB3_SRC_ALGORITHMS_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include "graph_utill.h"

namespace algorithms {
class BinaryHeap;

struct dijstra_return_data {
  size_t verticies;
  size_t edges;
  int lowest_cost;
  int highest_cost;
  double time;
  int path;
  size_t source = 0;
  size_t dest = 0;
  std::string toString() {
    return "verticies: [" + std::to_string(verticies) + "] edges: [" + std::to_string(edges) +
        "] lowest: [" + std::to_string(lowest_cost) + "] highest: [" + std::to_string(highest_cost)
        + "]";
  }
};

class PriorityQueue {
 public:
  class Vertice {
   public:
    size_t id;
    int weight;
    bool operator<(Vertice const &vertice) const {
      return this->weight < vertice.weight;
    }
    bool operator>(Vertice const &vertice) const {
      return this->weight > vertice.weight;
    }
  };
  size_t size;
  virtual ~PriorityQueue() = default;
  virtual void insert(Vertice vertice) {};
  virtual Vertice pop() {};
  virtual void decrease_key(Vertice vertice) {};
  virtual void emplace(size_t id, int weight) {};
  virtual bool empty() {};
};

class BinaryHeap : public PriorityQueue {
 private:
  std::unordered_map<size_t, size_t> vert_map;
  size_t capacity;
  size_t parent(size_t i) { return (i - 1) / 2; }

  size_t left(size_t i) { return (2 * i + 1); }

  size_t right(size_t i) { return (2 * i + 2); }

  void heapify(size_t i) {
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;
    if (l < size && data[l] < data[i])
      smallest = l;
    if (r < size && data[r] < data[smallest])
      smallest = r;
    if (smallest != i) {
      std::swap(data[i], data[smallest]);
      std::swap(vert_map[data[i].id], vert_map[data[smallest].id]);

      heapify(smallest);
    }
  }

 public:
  std::vector<Vertice> data;

  explicit BinaryHeap(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    data = std::vector<Vertice>(capacity);
//    vert_map = std::unordered_map<size_t ,size_t >();
  }

  void insert(Vertice vertice) override {
    size_t i = size;
//    if(i == data.capacity()){
//      data.push_back(vertice);
//    }else{
//      data[i] = vertice;
//    }
//    if(size == data.capacity()){
//      data.push_back({0,0});
//    }

    size++;
    data[i] = vertice;
    vert_map[vertice.id] = i;
    while (i != 0 && data[parent(i)] > data[i]) {
      std::swap(data[i], data[parent(i)]);
      std::swap(vert_map[data[i].id], vert_map[data[parent(i)].id]);
      i = parent(i);
    }
  };

  Vertice pop() override {
    if (size == 1) {
      size--;
      return data[0];
    }

    Vertice root = data[0];
    vert_map.erase(data[0].id);

    data[0] = data[size - 1];
    vert_map[data[0].id] = 0;
//    vert_map.erase(data[0].id);
    size--;
    heapify(0);

    return root;
  };

  void decrease_key(Vertice vertice) override {
    assert(vert_map.contains(vertice.id));
    auto i = vert_map[vertice.id];
    if (data[i].weight < vertice.weight)
      return;
    data[i].weight = vertice.weight;
    while (i != 0 && data[parent(i)] > data[i]) {
      std::swap(data[i], data[parent(i)]);
      std::swap(vert_map[data[i].id], vert_map[data[parent(i)].id]);
      i = parent(i);
    }
  };
  void delete_elem(Vertice vertice) {
    auto i = vert_map[vertice.id];
    while (i != 0) {
      std::swap(data[i], data[parent(i)]);
      std::swap(vert_map[data[i].id], vert_map[data[parent(i)].id]);
      i = parent(i);
    }
    pop();
  }
  void emplace(size_t id, int weight) override {
    insert({id, weight});
  };
  bool empty() override { return size == 0; };
};

class StdPriorityQueue : public PriorityQueue {
 private:
  class vertcompare {
   public:
    bool operator()(Vertice a, Vertice b) {
      return a.weight < b.weight;
    };
  };
  std::priority_queue<Vertice, std::vector<Vertice>, vertcompare> priority_queue;
 public:
  StdPriorityQueue() {
    size = 0;
  }
  void insert(Vertice vertice) override {
    priority_queue.push(vertice);
    size++;
  };
  void emplace(size_t id, int weight) override {
    priority_queue.push(PriorityQueue::Vertice{id, weight});
    size++;
  };
  Vertice pop() override {
    size--;
    auto v = priority_queue.top();
    priority_queue.pop();
    return v;
  };
  void decrease_key(Vertice vertice) override {
    insert(vertice);
  };
  bool empty() override {
    return size == 0;
  }
};

class DialPriorityQueue : public PriorityQueue {
 private:
  struct DialVertice {
    size_t vertice;
    int tag;
    std::_List_iterator<size_t> self = {};
    bool finilized = false;
  };
  size_t current_elem;
  size_t C;
  size_t size;
  std::vector<std::list<size_t>> containers;
  std::unordered_map<size_t, DialVertice> verticies_bank;

 public:
  DialPriorityQueue(size_t C, size_t n) {
    this->size = 0;
    this->current_elem = 0;
    this->C = C + 1;
    containers = std::vector<std::list<size_t>>(C + 1);
    verticies_bank.reserve(n);
  }
  void insert(algorithms::PriorityQueue::Vertice vertice) override {
    if (!verticies_bank.contains(vertice.id)) {
      size++;
      verticies_bank.insert({vertice.id,
                             DialVertice{.vertice = vertice.id, .tag = vertice.weight}});
      auto cont_id = (vertice.weight) % (C);
      containers[cont_id].push_front(vertice.id);
      verticies_bank[vertice.id].self = containers[cont_id].begin();
    } else
      assert(false);
  }
  Vertice pop() override {
    size--;
    while (containers[current_elem % (C )].empty()) {
      current_elem++;
    }
    assert(!containers[current_elem % (C)].empty());
    size_t elem = containers[current_elem % (C)].front();
    containers[current_elem % (C)].pop_front();
    verticies_bank[elem].finilized = true;

    return {elem, verticies_bank[elem].tag};
  }

  void decrease_key(Vertice vert) override {
    auto [id, tag] = vert;
    assert(verticies_bank.contains(id));
    auto &elem = verticies_bank[id];
    if (elem.finilized)
      return;
    if (elem.tag < tag) {
      return;
    }
    containers[elem.tag % (C)].erase(elem.self);
    containers[tag % (C)].push_front(id);
    elem.tag = tag;
    elem.self = containers[tag % (C)].begin();
  }

  bool empty() override {
    return size == 0;
  }
};

class RadixHeap : public PriorityQueue {
 private:
  struct container {
    size_t lower_bound;
    size_t upper_bound;
    BinaryHeap data;
    bool empty() const {
      return data.size == 0;
    }
    void erase(size_t id) {
      data.delete_elem({id, 0});
    }

    Vertice top() {
      return data.data[0];
    }

    Vertice pop() {
      return data.pop();
    }

    void push(Vertice vertice) {
      data.insert(vertice);
    }

    void clear() {
      data.data.clear();
      data.size = 0;
    }
  };

  void put(Vertice vertice) {
    auto x = std::find_if(containers.begin(), containers.end(), [vertice](const container &c) {
      return vertice.weight >= c.lower_bound && vertice.weight <= c.upper_bound;
    });
    assert(x != containers.end());
    x->push(vertice);
  }

  std::unordered_map<size_t, int> vert_weights;
  std::vector<container> containers;
  size_t C;
  size_t cont_pos;
  size_t cont_size;
 public:

  explicit RadixHeap(size_t C, size_t n) {
    this->C = C;
    this->cont_pos = 0;
    this->cont_size = (size_t) (std::log2(C * n) + 1);
    this->size = 0;
    vert_weights.reserve(n);
    containers = std::vector<container>(cont_size, {.data = BinaryHeap(n)});
    containers[0].lower_bound = containers[0].upper_bound = 0;
    containers[1].lower_bound = containers[1].upper_bound = 1;
    for (auto x = containers.begin() + 1; x < containers.end(); x++) {
      x->lower_bound = (x - 1)->upper_bound + 1;
      x->upper_bound = x->lower_bound * 2 - 1;
    }
  }

  void insert(Vertice vertice) override {
//    assert(!vert_weights.contains(vertice.id));
    size++;
    put(vertice);
    vert_weights.insert({vertice.id, vertice.weight});
  }

  Vertice pop() override {
    if (empty()) return {};
    size--;
    size_t curr_cont = 0;
    while (containers[curr_cont].data.empty()) {
      curr_cont++;
    }
    if (containers[curr_cont].lower_bound != containers[curr_cont].upper_bound) {
      auto elem = containers[curr_cont].top();
      size_t new_lower_bound = elem.weight;
      size_t new_upper_bound = containers[curr_cont].upper_bound;
      int to_be_updated = std::ceil(std::log2(new_upper_bound - new_lower_bound + 1) + 1);
      int i = -1;
      int p = 0;
      int last_upper_value = -1;
      while (last_upper_value != new_upper_bound) {
        i++;
        p *= 2;
        if (i == 0) {
          containers[0].lower_bound = containers[0].upper_bound = last_upper_value =
              new_lower_bound;
          continue;
        }
        if (i == 1) {
          containers[1].lower_bound = containers[1].upper_bound = last_upper_value =
              containers[0].lower_bound + 1;
          p = 1;
          continue;
        }
        containers[i].lower_bound = std::min(containers[i - 1].upper_bound + 1, new_upper_bound);
        containers[i].upper_bound = std::min(containers[i].lower_bound + p - 1, new_upper_bound);
        last_upper_value = containers[i].upper_bound;

      }
      i++;
      while (i <= curr_cont) {
        containers[i].upper_bound = 0;
        containers[i].lower_bound = 0;
        i++;
      }

      for (int j = 0; j < containers[curr_cont].data.size; j++) {
        put(containers[curr_cont].data.data[j]);
      }
      containers[curr_cont].clear();
      curr_cont = 0;
    }
    auto elem = containers[curr_cont].pop();

    return elem;
  }

  void decrease_key(Vertice vertice) override {
    assert(vert_weights.contains(vertice.id));
    auto vert_weight = vert_weights.at(vertice.id);
    if (vert_weight < vertice.weight)
      return;
    int past_weight = vert_weight;
    auto x = std::find_if(containers.begin(), containers.end(), [past_weight](const container &c) {
      return past_weight >= c.lower_bound && past_weight <= c.upper_bound;
    });
    if(x->upper_bound >= vertice.weight && x->lower_bound <= vertice.weight){
      x->data.decrease_key(vertice);
    } else{
      x->erase(vertice.id);
      put(vertice);
    }
    vert_weights[vertice.id] = vertice.weight;

  }

  void emplace(size_t id, int weight) override {
    insert({id, weight});
  }

  bool empty() override {
    return size == 0;
  }
};

dijstra_return_data runDijsktra(Graph graph, size_t source, size_t goal, std::unique_ptr<PriorityQueue> &container);
}
#endif //LAB3_SRC_ALGORITHMS_H_
