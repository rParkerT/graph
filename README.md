Graph is data structure that consists of set of vertices and edges.
Edges are lines or arcs that connect any two given nodes in the graph. Graph is
usually represented using list or matrix. This implemented code is mostly based on list idea,
in a sense that Vertex as Node in list is defined, but instead of adding vertex as head Node
in array or vectors of lists, vector of Vertices was used. Added Vertices to edges are part
of Vertex structure.

CMake is used for project build. For building tests for testGraphStore.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./tests

To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests

GraphStoreLinked class has graph functions, which are implemented in LinkedListOfVertices class.
Class LinkedVertices has head node and vector of edges that are connected to this head node.
Dijkstra algorithm is implemented.

Benchmark results:

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Add 100.000 vertex in graph                    100             1     28.2853 s
                                        60.6066 ms    60.4757 ms    60.8235 ms
                                        842.086 us    576.893 us    1.19179 ms

Add 100.000 edges in graph of 100.
000 vertices                                   100             1     19.2715 s
                                        169.455 ms    163.398 ms    186.252 ms
                                        47.0961 ms    18.5053 ms    98.8359 ms

-------------------------------------------------------------------------------
Graph Store search shortest path - Benchmark
-------------------------------------------------------------------------------
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Find 100 shortest paths in graph of
100.000 vertices                               100             1     2.58232 s
                                        25.7683 ms    25.7384 ms    25.8109 ms
                                        180.098 us      137.5 us    233.566 us
