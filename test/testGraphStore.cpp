#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "graphStoreLinked.h"
#include <catch.hpp>

TEST_CASE("Graph Store insert vertices, edges, add and remove labels for int "
          "data type") {
  graph::GraphStoreLinked<int> graph;
  CHECK(graph.addVertex(1, 1) == true);
  CHECK(graph.addVertex(2, 2) == true);
  CHECK(graph.addVertex(3, 3) == true);
  CHECK(graph.addVertex(3, 3) != true);

  CHECK(graph.addLabel(1, "a") == true);
  CHECK(graph.addLabel(2, "a", "b") == true);
  CHECK(graph.addLabel(1, "b") == true);
  CHECK(graph.addLabel(3, "a", "b", "c", "d", "all alphabet.....") == true);
  CHECK(graph.addLabel(5, "string") == false);

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);
  graph.getVertexInfo(5);

  CHECK(graph.removeLabel(1, "a", "e") == false);
  CHECK(graph.removeLabel(2, "string") == false);
  CHECK(graph.removeLabel(3, "a", "c") == true);

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);

  CHECK(graph.createEdge(1, 2) == true);
  CHECK(graph.createEdge(1, 3) == true);
  CHECK(graph.createEdge(1, 4) == false);
  CHECK(graph.createEdge(10, 1) == false);
  CHECK(graph.createEdge(2, 5) == false);
  CHECK(graph.createEdge(2, 1) == true);
  CHECK(graph.createEdge(2, 1) == true);
}

TEST_CASE("Graph Store insert vertices, edges, add and remove labels for float "
          "data type") {
  graph::GraphStoreLinked<float> graph;
  CHECK(graph.addVertex(1, 1.1) == true);
  CHECK(graph.addVertex(2, 2.22) == true);
  CHECK(graph.addVertex(3, 3.33) == true);
  CHECK(graph.addVertex(3, 3.33) != true);

  CHECK(graph.addLabel(1, "abcd") == true);
  CHECK(graph.addLabel(2, "ab", "bb") == true);
  CHECK(graph.addLabel(1, "b b b b b") == true);
  CHECK(graph.addLabel(3, "") == true);
  CHECK(graph.addLabel(5, "sdgsfgbfdbvcbdfbdzf") == false);

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);
  graph.getVertexInfo(5);

  CHECK(graph.removeLabel(1, "abcd", "e") == false); // e is not inserted
  CHECK(graph.removeLabel(1, "abcd") == false);      // abcd is already removed

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);

  CHECK(graph.createEdge(1, 2) == true);
  CHECK(graph.createEdge(1, 3) == true);
  CHECK(graph.createEdge(1, 4) == false);
  CHECK(graph.createEdge(10, 1) == false);
  CHECK(graph.createEdge(2, 5) == false);
  CHECK(graph.createEdge(2, 1) == true);
  CHECK(graph.createEdge(2, 1) == true);
}

TEST_CASE("Graph Store insert vertices, edges, add and remove labels for "
          "TestStringObject "
          "data type") {

  struct TestStringObject {
    std::string name;
    int age;
  };
  struct TestStringObject a = {"Ana", 25};
  struct TestStringObject l = {"Lily", 30};
  struct TestStringObject j = {"Joe", 35};

  graph::GraphStoreLinked<TestStringObject> graph;
  CHECK(graph.addVertex(1, a) == true);
  CHECK(graph.addVertex(2, l) == true);
  CHECK(graph.addVertex(3, j) == true);
  CHECK(graph.addVertex(3, j) != true);

  CHECK(graph.addLabel(1, "abcd") == true);
  CHECK(graph.addLabel(2, "ab", "bb") == true);
  CHECK(graph.addLabel(1, "b b b b b") == true);
  CHECK(graph.addLabel(3, "") == true);
  CHECK(graph.addLabel(5, "sdgsfgbfdbvcbdfbdzf") == false);

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);
  graph.getVertexInfo(5);

  CHECK(graph.removeLabel(1, "abcd") == true);
  CHECK(graph.removeLabel(2, "ab") == true);
  CHECK(graph.removeLabel(2, "bb") == true);

  graph.getVertexInfo(1);
  graph.getVertexInfo(2);
  graph.getVertexInfo(3);

  CHECK(graph.createEdge(1, 2) == true);
  CHECK(graph.createEdge(1, 3) == true);
  CHECK(graph.createEdge(1, 4) == false);
  CHECK(graph.createEdge(10, 1) == false);
  CHECK(graph.createEdge(2, 5) == false);
  CHECK(graph.createEdge(2, 1) == true);
  CHECK(graph.createEdge(2, 1) == true);
}

TEST_CASE("Graph Store insert vertexex - Benchmark") {
  graph::GraphStoreLinked<int> graph;
  BENCHMARK("Add 100.000 vertex in graph") {
    for (int j = 0; j < 100000; j++) {
      graph.addVertex(j, j);
    }
  };

  BENCHMARK("Add 100.000 edges in graph of 100.000 vertices") {
    for (int j = 0; j < 10000; j++) {
      graph.createEdge(j, j + 1000);
      graph.createEdge(j, j + 2100);
      graph.createEdge(j, j + 3110);
      graph.createEdge(j, j + 4111);
      graph.createEdge(j, j + 5200);
      graph.createEdge(j, j + 1220);
      graph.createEdge(j, j + 2222);
      graph.createEdge(j, j + 3300);
      graph.createEdge(j, j + 4330);
      graph.createEdge(j, j + 5333);
    }
  };
}

TEST_CASE("Graph Store find shortest path") {
  graph::GraphStoreLinked<int> graph;
  for (int j = 0; j < 16; j++) {
    graph.addVertex(j, j);
  }

  CHECK(graph.createEdge(1, 2) == true);
  CHECK(graph.createEdge(2, 3) == true);
  CHECK(graph.createEdge(3, 5) == true);
  CHECK(graph.createEdge(2, 5) == true);

  CHECK(graph.addLabel(1, "a") == true);
  CHECK(graph.addLabel(2, "a") == true);
  CHECK(graph.addLabel(3, "a") == true);
  CHECK(graph.addLabel(4, "a") == true);
  CHECK(graph.addLabel(5, "a") == true);

  CHECK(graph.shortestPath(1, 15, "a") == false);
  CHECK(graph.shortestPath(1, 5, "a") == true);

  REQUIRE(graph.createEdge(1, 4) == true);
  REQUIRE(graph.createEdge(4, 5) == true);
  REQUIRE(graph.createEdge(5, 6) == true);
  REQUIRE(graph.createEdge(6, 7) == true);
  REQUIRE(graph.createEdge(7, 8) == true);
  REQUIRE(graph.createEdge(4, 7) == true);

  REQUIRE(graph.addLabel(6, "a") == true);
  REQUIRE(graph.addLabel(8, "a") == true);

  REQUIRE(graph.shortestPath(1, 8, "a") == false);
  REQUIRE(graph.shortestPath(6, 8, "a") == false);
  REQUIRE(graph.addLabel(7, "a") == true);
  REQUIRE(graph.shortestPath(1, 8, "a") == true);

  REQUIRE(graph.addLabel(10, "") == true);
  REQUIRE(graph.addLabel(11, "") == true);
  REQUIRE(graph.addLabel(12, "") == true);
  REQUIRE(graph.addLabel(13, "") == true);
  REQUIRE(graph.addLabel(14, "") == true);
  REQUIRE(graph.addLabel(15, "") == true);

  REQUIRE(graph.createEdge(10, 14) == true);
  REQUIRE(graph.createEdge(14, 13) == true);
  REQUIRE(graph.createEdge(13, 15) == true);

  REQUIRE(graph.shortestPath(10, 15, "") == true);

  REQUIRE(graph.addLabel(1, "a") == true);
  REQUIRE(graph.addLabel(2, "b", "a") == true);
  REQUIRE(graph.addLabel(5, "c", "a") == true);
  REQUIRE(graph.shortestPath(1, 5, "a") == true);
  REQUIRE(graph.shortestPath(1, 5, "a", "b") == false);

  CHECK(graph.shortestPath(1, 25, "a") == false);
}

TEST_CASE("Graph Store search shortest path - Benchmark") {
  graph::GraphStoreLinked<int> graph;
  graph.disableOutputPrint();
  for (int j = 0; j < 100000; j++) {
    graph.addVertex(j, j);
  }
  for (int j = 0; j < 100000; j++) {
    graph.addLabel(j, "a", "");
  }
  graph.createEdge(1, 2);
  graph.createEdge(2, 3);
  graph.createEdge(3, 5);
  graph.createEdge(5, 7);
  graph.createEdge(7, 11);
  graph.createEdge(11, 13);
  graph.createEdge(13, 17);
  graph.createEdge(17, 19);
  graph.createEdge(19, 23);
  graph.createEdge(23, 29);
  graph.createEdge(295, 315);
  graph.createEdge(37, 73);
  graph.createEdge(73, 97);
  graph.createEdge(97, 990);
  graph.createEdge(990, 66);
  graph.createEdge(5678, 9981);
  graph.createEdge(13, 2985);
  graph.createEdge(2985, 16543);
  graph.createEdge(16543, 28555);
  graph.createEdge(28555, 13);
  graph.createEdge(66005, 33010);
  graph.createEdge(33000, 11);

  BENCHMARK("Find 100 shortest paths in graph of 100.000 vertices") {
    for (int i = 0; i < 10; ++i) {
      graph.shortestPath(1, 9981, "a");
      graph.shortestPath(2, 97, "a");
      graph.shortestPath(19, 33010, "a");
      graph.shortestPath(11, 33010, "a");
      graph.shortestPath(33, 73, "a");
      graph.shortestPath(7, 66005, "a");
      graph.shortestPath(5, 29, "a");
      graph.shortestPath(37, 97, "a");
      graph.shortestPath(295, 990, "a");
      graph.shortestPath(13, 5678, "a");
    }
  };
}
