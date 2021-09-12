#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace graph {

/**
 * Implementation of the Linked Vertices class.
 *
 * Linked Vertices is a linear collection of data elements in which every
 * element has id, data, labelVec, vector of labels for that Node, distance and
 * previous, elements used in Dijkstra algorithm. Class has head Node Vertex and
 * vector of edges that are connected to head Node Vertex.
 *
 * @tparam V type of data stored in Linked Vertices
 */
template <typename V> class LinkedVertices {
public:
  /**
   * Implementation of the NodeVertex structure.
   *
   * Each NodeVertex carries a key and a pointer to next Node.
   *
   * @param id id of NodeVertex
   * @tparam V data type in NodeVertex
   */
  struct NodeVertex {
    int id;                            ///< NodeVertex id
    V data;                            ///< NodeVertex data
    std::vector<std::string> labelVec; ///< Vertex label
    int distance =
        std::numeric_limits<int>::max(); ///< Used in Dijkstra alghorithm
    int previous =
        std::numeric_limits<int>::min(); ///< Used in Dijkstra alghorithm

    /**
     * Node constructor.
     * Each NodeVertex is constructed using key value.
     *
     * @param vertexKey Vertex id
     */
    explicit NodeVertex(int vertexKey) : id(vertexKey) {}

    /**
     * Node constructor.
     * Each NodeVertex is constructed using key value and data of
     * NodeVertex.
     *
     * @param vertexKey Vertex id
     * @tparam info Vertex data
     */
    explicit NodeVertex(int vertexKey, V info) : id(vertexKey), data(info) {}

    /**
     * Sets distance of node vertex to new distance value
     *
     * @param distance new distance of node vertex
     */
    void setVertexDistance(int distance) { this->distance = distance; }

    /**
     * Sets previous node of node vertex to new previous value
     *
     * @param previous new previous of node vertex
     */
    void setPreviousNode(int previous) { this->previous = previous; }

    /**
     * Returns distance of node vertex
     */
    int getVertexDistance() { return this->distance; }

    /**
     * Returns previous of node vertex
     */
    int getPreviousNode() { return this->previous; }

    /**
     * Checks if labelVec of node vertex contains all labels and returns true if
     * does
     *
     * @param label vector of labels for which is checked if it is inserted in
     * labelVec
     */
    bool hasLabel(std::vector<std::string> &label) const {
      return std::includes(this->labelVec.begin(), this->labelVec.end(),
                           label.begin(), label.end());
    }
  };

  /**
   * Head node vertex.
   */
  std::shared_ptr<NodeVertex> head = nullptr;

  /**
   * Vector of edges that are connected to head node vertex.
   */
  std::vector<std::shared_ptr<NodeVertex>> nodes;

public:
  /**
   * Constructor of LinkedVertices
   *
   * During LinkedVertices object construction,
   * head NodeVertex is created, with vertexKey as id and info as data
   *
   * @param vertexKey id of node vertex head
   * @tparam info node vertex head data
   */
  explicit LinkedVertices(int vertexKey, const V &info);

  /**
   * Destructor  of Linked List
   *
   * Default implementation
   *
   */
  ~LinkedVertices();

  /// Disabling construction of Linked List object using copy constructor
  LinkedVertices(const LinkedVertices &rhs) = delete;

  /// Disabling construction of Linked List object using copy assignment
  LinkedVertices &operator=(const LinkedVertices &rhs) = delete;

  /**
   * Inserts node vertex newNode in vector of node vertices nodes
   *
   * @param newNode node that is inserted in nodes
   */
  void insertNodeVertex(const std::shared_ptr<NodeVertex> newNode);

  /**
   * Returns ptr to head node
   *
   */
  std::shared_ptr<NodeVertex> getHead() const;

  /**
   * Returns info for head node vertex, id and labels
   *
   */
  void getVertexInfo() const;

  /**
   * Adds label to labelVec of head
   *
   * @param label that is to be inserted in labelVec
   */
  void addLabel(const std::string &label);

  /**
   * Removes label from labelVec of head. returns true if that label was not
   * found in labelVec.
   *
   * @param label that is to be removed from labelVec
   */
  bool removeLabel(const std::string &label);

  /**
   * Returns vertices that are connected to head node
   *
   */
  std::vector<std::shared_ptr<NodeVertex>> returnEdges();
};

template <typename V>
LinkedVertices<V>::LinkedVertices(int vertexKey, const V &info) {
  head = std::make_shared<NodeVertex>(vertexKey, info);
}

template <typename V> LinkedVertices<V>::~LinkedVertices() {}

template <typename V>
void LinkedVertices<V>::insertNodeVertex(
    const std::shared_ptr<NodeVertex> newNode) {
  nodes.push_back(newNode);
}

template <typename V>
std::shared_ptr<typename LinkedVertices<V>::NodeVertex>
LinkedVertices<V>::getHead() const {
  return head;
}

template <typename V>
void LinkedVertices<V>::addLabel(const std::string &label) {
  head->labelVec.push_back(label);
  std::sort(head->labelVec.begin(), head->labelVec.end());
}

template <typename V>
bool LinkedVertices<V>::removeLabel(const std::string &label) {
  size_t labelVecBefore = head->labelVec.size();
  head->labelVec.erase(
      std::remove(head->labelVec.begin(), head->labelVec.end(), label),
      head->labelVec.end());
  if (labelVecBefore == head->labelVec.size()) {
    std::sort(head->labelVec.begin(), head->labelVec.end());
    return false;
  }
  std::sort(head->labelVec.begin(), head->labelVec.end());
  return true;
}

template <typename V> void LinkedVertices<V>::getVertexInfo() const {
  std::cout << "Node id " << head->id << " , label ";
  for (const auto &l : head->labelVec) {
    std::cout << l << " ";
  }
  std::cout << std::endl;
}

template <typename V>
std::vector<std::shared_ptr<typename LinkedVertices<V>::NodeVertex>>
LinkedVertices<V>::returnEdges() {
  return nodes;
}

} // namespace graph
