#pragma once

#include "linkedVertices.h"
#include <deque>
#include <list>
#include <map>

namespace graph {

/**
 * Implementation of the methods used in graph data structure. This class uses
 * modified linked list to insert vertices and edges. When the vertex is
 * created, it is inserted as a head vertex in LinkedVertices class, by adding
 * edges to this vertex, we add edge vertex to a vector of edges in
 * LinkedVertices. Each created LinkedVertices object is inserted in map
 * vertexList, where key is an id of head vertex. Map was chosen because it
 * provides an efficient search of vertices.
 *
 */
template <typename V> class LinkedListOfVertices {
private:
  /**
   * Map of pair < key of head vertex, ptr to entire LinkedVertices<V> that
   * containes head Vertex and all of the edges connected to head vertex>
   */
  std::map<int, std::shared_ptr<LinkedVertices<V>>> vertexList = {};

  /**
   * Checks if key of vertex is inserted in vertexList map.
   *
   * @param key key id of Vertex
   * return true if vertex is inserted in vertexList
   */
  bool keyFoundInVertexListAsHead(int key);

  /**
   * Used in Dijkstra algorithm, copy of qBackUp entries
   */
  std::list<int> q;

  /**
   * Used in Dijkstra algorithm, all keys of edges inserted in vertexList, no
   * duplicates and sorted
   */
  std::list<int> qBackUp;

  /**
   * Used in Dijkstra algorithm to print out shortest path between two Vertices
   */
  std::deque<int> path;

  /**
   * Added parameter for testing purposes, if set to true, there is a console
   * display of Vertices on shortest path between 2 given Vertices
   */
  bool enableOutputPrint = true;

public:
  /**
   * Constructor of LinkedListOfVertices
   *
   * Constructor takes no arguments. Default implementation.
   *
   */
  LinkedListOfVertices() = default;

  /**
   * Destructor  of Linked List
   *
   * Default implementation.
   *
   */
  ~LinkedListOfVertices();

  /// Disabling construction of Linked List object using copy constructor
  LinkedListOfVertices(const LinkedListOfVertices &rhs) = delete;

  /// Disabling construction of Linked List object using copy assignment
  LinkedListOfVertices &operator=(const LinkedListOfVertices &rhs) = delete;

  /**
   * Add Vertex to Graph
   *
   * This method checks if this vertex is already inserted in vertexList, if
   * yes, it returns false. If vertex is not already inserted, new pair is
   * created in vertexList, that has key parameter as key of vertexList and
   * LinkedVertices is created, with the head vertex with key as vertex id.
   *
   * @param key id of Vertex
   * @tparam info Vertex info
   *
   * @return true if vertexList does not contain this key
   */
  bool insertNodeVertexAsHead(int key, const V &info);

  /**
   * Create Edge in Graph
   *
   * This method checks if both start and stop vertex are already inserted in
   * vertexList, if not, it returns false. If they are, vertexList is searched
   * for start key and in LinkedVertices, that has a head with this key, stop
   * vertex is added in vector of edges.
   *
   * @param start id of source Vertex
   * @param stop id of destination Vertex
   *
   * @return true if vertexList has both start and stop vertex
   */
  bool addEdgeToHeadNodeVertex(int start, int stop);

  /**
   * Add Label to Vertex
   *
   * This method checks if this vertex is inserted in vertexList, if
   * yes, it returns true. Before return, LinkedVertices method void
   * addLabel(const std::string &label) is called, that inserts label in
   * labelVec of head vertex.
   *
   * @param key id of Vertex
   * @param label Vertex label
   *
   * @return true if if vertexList has key vertex
   */
  bool addLabelToVertex(int key, const std::vector<std::string> &label);

  /**
   * Add Label to Vertex
   *
   * This method checks if this vertex is inserted in vertexList, if
   * yes, it returns true. Before return, LinkedVertices method void
   * removeLabel(const std::string &label) is called, that removes label from
   * labelVec of head vertex.
   *
   * @param key id of Vertex
   * @param label Vertex label
   *
   * @return true if if vertexList has key vertex
   */
  bool removeLabelFromVertex(int key, const std::vector<std::string> &label);

  /**
   * This method checks if this vertex is inserted in vertexList, if
   * yes, it calls for LinkedVertices method void getVertexInfo(int key) const
   * on head vertex.
   *
   * @param key key id of Vertex
   */
  void getVertexInfo(int key);

  /**
   * Finds shortest path between two Vertices in Graph
   *
   * This method uses Dijkstra algorithm. Step by step explenation is given in
   * function comments.
   *
   * @tparam start key id of source Vertex
   * @tparam stop key id of destination Vertex
   * @param label label of Vertices found on shortest path
   *
   * @return true if there is a path between two vertices, where each vertex on
   * the path has label
   */
  bool findShortestPath(int start, int stop, std::vector<std::string> &label);

  /**
   * Disables console print of Vertices that are found in function
   * shortestPath(int start, int stop, std::vector<std::string>
   * &label).
   *
   * Helper function added for testing purposes, when benchmark is run.
   */
  void disableOutputPrint() { enableOutputPrint = false; }
};

template <typename V> LinkedListOfVertices<V>::~LinkedListOfVertices() {}

template <typename V>
bool LinkedListOfVertices<V>::keyFoundInVertexListAsHead(int key) {
  if (vertexList.find(key) != vertexList.end())
    return true;
  return false;
}

template <typename V>
bool LinkedListOfVertices<V>::insertNodeVertexAsHead(int key, const V &info) {
  if (keyFoundInVertexListAsHead(key))
    return false;
  else {
    vertexList.insert(std::pair<int, std::shared_ptr<LinkedVertices<V>>>(
        key, std::make_shared<LinkedVertices<V>>(key, info)));
    return true;
  }
}

template <typename V>
bool LinkedListOfVertices<V>::addEdgeToHeadNodeVertex(int start, int stop) {
  auto itStart = vertexList.find(start);
  auto itStop = vertexList.find(stop);

  if (itStart != vertexList.end() && itStop != vertexList.end()) {
    itStart->second->insertNodeVertex(itStop->second->getHead());
    // if the vertexList has a lot of vertices, but not so many connected edges,
    // it is more efficient to store keys of connected vertices in qBackUp list
    // to be used in Dijkstra algorithm
    qBackUp.push_back(start);
    qBackUp.push_back(stop);
    return true;
  }
  return false;
}

template <typename V>
bool LinkedListOfVertices<V>::addLabelToVertex(
    int key, const std::vector<std::string> &label) {
  auto itNode = vertexList.find(key);
  if (itNode != vertexList.end()) {
    for (const auto &l : label) {
      itNode->second->addLabel(l);
    }
    return true;
  }
  return false;
}

template <typename V>
bool LinkedListOfVertices<V>::removeLabelFromVertex(
    int key, const std::vector<std::string> &label) {
  bool hasThisString = true;
  auto itNode = vertexList.find(key);
  if (itNode != vertexList.end()) {
    for (auto l : label) {
      if (!itNode->second->removeLabel(l))
        hasThisString = false;
    }
    return hasThisString;
  }
  return hasThisString;
}

template <typename V> void LinkedListOfVertices<V>::getVertexInfo(int key) {
  for (auto &vertex : vertexList) {
    if (vertex.second->getHead()->id == key) {
      vertex.second->getVertexInfo();
    }
  }
}

template <typename V>
bool LinkedListOfVertices<V>::findShortestPath(
    int start, int stop, std::vector<std::string> &label) {

  auto startNode = vertexList.find(start);
  auto stopNode = vertexList.find(stop);

  // if the vertexList does not contain start or stop key, return false and do
  // not proceed with calculation
  if (startNode == vertexList.end() || stopNode == vertexList.end()) {
    std::cout << "No start or stop node in graph" << std::endl;
    return false;
  }

  // sort keys of connected vertices in qBackUp and remove duplicates
  qBackUp.sort();
  qBackUp.unique();

  // clear q list and path deque, in case they contain infos from previous
  // calculations
  path.clear();
  q.clear();

  // loop through qBackUp and set each entry distance to INF and previous
  // visited vertex to -INF and copy all entries in q list
  for (const auto &element : qBackUp) {
    q.push_back(element);
    auto node = vertexList.find(element);
    node->second->getHead()->setVertexDistance(std::numeric_limits<int>::max());
    node->second->getHead()->setPreviousNode(std::numeric_limits<int>::min());
  }

  // set distance of start vertex to 0
  startNode->second->getHead()->setVertexDistance(0);

  int tempNodeKey = 0;

  // loop until q is empty
  while (!q.empty()) {
    // take first key from q list and save it in int u
    int u = q.front();

    // check if any of the keys in q list has smaller distance then the distance
    // of u, if yes, save that one in u
    for (auto current : q) {
      if (vertexList.find(current)->second->getHead()->getVertexDistance() <
          vertexList.find(u)->second->getHead()->getVertexDistance()) {
        u = current;
      }
    }
    // if u is stop key, clear q list, since this is destination vertex, no need
    // for further calculation
    if (u == stop) {
      tempNodeKey = u;
      q.clear();
    }

    // we do a calculation for u, so we can remove it from q list
    q.remove(u);
    // for every connected edge to u, we check if its distance is greater then u
    // distance, and does it have that label, if yes, set distance of edge to
    // distance of u + 1 and previous visited vertex to u
    for (auto edge : vertexList.find(u)->second->returnEdges()) {
      int newDistance =
          vertexList.find(u)->second->getHead()->getVertexDistance();

      if (newDistance < edge->getVertexDistance() && edge->hasLabel(label)) {
        edge->setVertexDistance(newDistance + 1);
        edge->setPreviousNode(u);
      }
    }
  }

  // first fetch LinkedVertices for tempNodeKey that is stop key, if exists
  if (vertexList.find(tempNodeKey)->second != nullptr) {
    // while previous vertex is not -INF, push at the front path deque previous
    // vertex id value
    while (vertexList.find(tempNodeKey)->second->getHead()->getPreviousNode() !=
           std::numeric_limits<int>::min()) {
      path.push_front(
          vertexList.find(tempNodeKey)->second->getHead()->getPreviousNode());
      // fetch previous vertex and save it as new tempNodeKey value
      tempNodeKey =
          vertexList.find(tempNodeKey)->second->getHead()->getPreviousNode();
    }
  }

  // if above check inserted some values in path, it means that there is a
  // shortest path between two vertices
  if (path.size() > 0) {
    // if not benchmark testing, print vertices ids on the shortest path between
    // start and stop vertex
    if (enableOutputPrint == true) {
      std::cout << "Start Vertex: " << startNode->first
                << " to Stop Vertex: " << stopNode->first << " shortest path: ";
      for (const auto p : path) {
        std::cout << vertexList.find(p)->first << "->";
      }
      std::cout << stopNode->first << std::endl;
    }
    return true;
  }
  // no path between two vertices, return false
  return false;
}

} // namespace graph
