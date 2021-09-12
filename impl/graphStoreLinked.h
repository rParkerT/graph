#pragma once

#include "linkedListOfVertices.h"

namespace graph {

/**
 * Implementation of the GraphStoreLinked class.
 *
 * Graph is data structure that consists of set of vertices and edges. Edges are
 * pairs of vertices. Class GraphStoreLinked is used as an interface for
 * LinkedListOfVertices class where graph methods are implemented.
 *
 */
template <typename V> class GraphStoreLinked {
private:
  /**
   * Object of LinkedListOfVertices<V> class
   */
  LinkedListOfVertices<V> linkedListOfVertices;

public:
  /**
   * Constructor of Graph Store
   *
   * Constructor takes no arguments. It instantiates object of
   * LinkedListOfVertices<V> class
   *
   */
  GraphStoreLinked();

  /**
   * Destructor  of Graph Store
   *
   * All vector elements are erased from vertexList
   *
   */
  ~GraphStoreLinked();

  /// Disabling construction of Graph Store object using copy constructor
  GraphStoreLinked(const GraphStoreLinked &rhs) = delete;

  /// Disabling construction of Graph Store object using copy assignment
  GraphStoreLinked &operator=(const GraphStoreLinked &rhs) = delete;

  /**
   * Add Vertex to Graph
   *
   * Calls for LinkedListOfVertices method bool insertNodeVertexAsHead(int key,
   * const V &info). If insertNodeVertexAsHead returns true, this is true then.
   *
   * @param key id of Vertex
   * @tparam info Vertex info
   *
   * @return true if LinkedListOfVertices method insertNodeVertexAsHead returns
   * true
   */
  bool addVertex(int key, const V &info);

  /**
   * Add Label to Vertex
   *
   * Calls for LinkedListOfVertices method bool addLabelToVertex(int key, const
   * std::vector<std::string> &label). If addLabelToVertex returns true,
   * this is true then.
   *
   * @param key id of Vertex
   * @param label Vertex label
   *
   * @return true if LinkedListOfVertices method addLabelToVertex returns
   * true
   */
  bool addLabel(int key, const std::vector<std::string> &label);

  /**
   * Variadic template function Add Label to Vertex
   *
   * Saves all string arguments into string vector and calls addLabel(int
   * key, const std::vector<std::string> &label)
   *
   * @param key id of Vertex
   * @tparam args string arguments
   *
   * @return return value of addLabel(int
   * key, const std::vector<std::string> &label)
   */
  template <typename... Args> bool addLabel(int key, const Args &... args) {
    std::vector<std::string> vecLabels;
    (vecLabels.push_back(args), ...);
    return addLabel(key, vecLabels);
  }

  /**
   * Create Edge in Graph
   *
   * Calls for LinkedListOfVertices method bool addEdgeToHeadNodeVertex(int
   * start, int stop). If addEdgeToHeadNodeVertex returns true,
   * this is true then.
   *
   * @param start id of source Vertex
   * @param stop id of destination Vertex
   *
   * @return true if LinkedListOfVertices method addEdgeToHeadNodeVertex returns
   * true
   */
  bool createEdge(int start, int stop);

  /**
   * Remove Label from Vertex
   *
   * Calls for LinkedListOfVertices method bool removeLabelFromVertex(int key,
   * const std::vector<std::string> &label). If removeLabelFromVertex returns
   * true, this is true then.
   *
   * @param key id of Vertex
   * @param labelsToRemove labels to remove from Vertex label
   *
   * @return true if LinkedListOfVertices method removeLabel returns
   * true
   */
  bool removeLabel(int key, const std::vector<std::string> &labelsToRemove);

  /**
   * Variadic template function Remove Label from Vertex
   *
   * Saves all string arguments into string vector and calls removeLabel(int
   * key, const std::vector<std::string> &labelsToRemove)
   *
   * @param key id of Vertex
   * @tparam args string arguments
   *
   * @return return value of removeLabel(int key, const std::vector<std::string>
   * &labelsToRemove)
   */
  template <typename... Args> bool removeLabel(int key, const Args &... args) {
    std::vector<std::string> labelsToRemove;
    (labelsToRemove.push_back(args), ...);
    return removeLabel(key, labelsToRemove);
  }

  /**
   * Finds shortest path between two Vertices in Graph
   *
   * Calls for LinkedListOfVertices method bool findShortestPath(int key,
   * const std::vector<std::string> &label). If findShortestPath returns
   * true, this is true then.
   *
   * @tparam start key id of source Vertex
   * @tparam stop key id of destination Vertex
   * @param label label of Vertices found on shortest path
   *
   * @return true if LinkedListOfVertices method findShortestPath returns
   * true
   */
  bool shortestPath(int start, int stop, std::vector<std::string> &label);

  /**
   * Variadic template function Finds shortest path between two Vertices in
   Graph
   *
   * Saves all string arguments into string vector and calls
   shortestPath(Vertex<V> *startV, Vertex<V> *stopV, std::vector<std::string>
   &label)
   *
   * @tparam start key id of source Vertex
   * @tparam stop key id of destination Vertex
   * @param label label of Vertices found on shortest path
   *
   * @return return value of shortestPath(int start, int stopV,
                     std::vector<std::string> &label)
   */
  template <typename... Args>
  bool shortestPath(int start, int stop, Args &... args) {
    std::vector<std::string> labelsToCheckOnPath;
    (labelsToCheckOnPath.push_back(args), ...);
    return shortestPath(start, stop, labelsToCheckOnPath);
  }

  /**
   * Calls for LinkedListOfVertices method void getVertexInfo(int key).
   *
   * @param key key id of Vertex
   */
  void getVertexInfo(int key);

  /**
   * Disables console print of Vertices that are found in function
   * shortestPath(int start, int stopV,
                     std::vector<std::string> &label)
   *
   * Helper function added for testing purposes.
   *
   */
  void disableOutputPrint();
};

template <typename V>
GraphStoreLinked<V>::GraphStoreLinked() : linkedListOfVertices() {}

template <typename V> GraphStoreLinked<V>::~GraphStoreLinked() {}

template <typename V>
bool GraphStoreLinked<V>::addVertex(int key, const V &info) {
  return linkedListOfVertices.insertNodeVertexAsHead(key, info);
}

template <typename V>
bool GraphStoreLinked<V>::createEdge(int start, int stop) {
  return linkedListOfVertices.addEdgeToHeadNodeVertex(start, stop);
}

template <typename V>
bool GraphStoreLinked<V>::addLabel(int key,
                                   const std::vector<std::string> &label) {
  return linkedListOfVertices.addLabelToVertex(key, label);
}

template <typename V>
bool GraphStoreLinked<V>::removeLabel(int key,
                                      const std::vector<std::string> &label) {
  return linkedListOfVertices.removeLabelFromVertex(key, label);
}

template <typename V> void GraphStoreLinked<V>::getVertexInfo(int key) {
  linkedListOfVertices.getVertexInfo(key);
}

template <typename V>
bool GraphStoreLinked<V>::shortestPath(int start, int stop,
                                       std::vector<std::string> &label) {
  return linkedListOfVertices.findShortestPath(start, stop, label);
}

template <typename V> void GraphStoreLinked<V>::disableOutputPrint() {
  linkedListOfVertices.disableOutputPrint();
}

} // namespace graph
