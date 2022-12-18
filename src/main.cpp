#include <iostream>
#include <iomanip>
#include <string>
#include "map.h"

// forward declarations
Map::Map *make_marietta_map();
Map::Intersection **make_marietta_nodes(Map::Map *map);
void make_marietta_edges(Map::Map *map, Map::Intersection **nodes);
Graph::Path find_shortest_path(Graph::Node *s, Graph::Node *t, Graph::UndirectedGraph *graph);

void print_gps_coordinates(Graph::Path &path)
{
  std::cout << "path-coordinates: ";
  std::cout << std::setprecision(12);

  LinkedList::Iterator<Graph::Node *> it = path.path->begin();
  for (; it != path.path->end(); it++)
  {
    Map::Intersection *node = (Map::Intersection *)*it;
    //std::cout << "(" << node->get_lat() << "," << node->get_lon() << ") ";
    std::cout << std::endl
              << "," << node->get_lat() << node->get_lon();
  }
  std::cout << std::endl;
  std::cout << "to visualize: upload the coordinates to https://www.google.com/maps/d/" << std::endl;
}

void test_one()
{
  std::cout << "========================================" << std::endl;
  std::cout << "TEST_ONE (example from slides)" << std::endl;

  Graph::UndirectedGraph graph;
  // the following constructs the example from Carey's slides, lecture 16
  // nodes A B C D
  // edges A-B, A-C, A-D, B-C, B-D, C-D
  Graph::Node *node_A = graph.add_node();
  Graph::Node *node_B = graph.add_node();
  Graph::Node *node_C = graph.add_node();
  Graph::Node *node_D = graph.add_node();
  graph.add_edge(node_A, node_B, 10);
  graph.add_edge(node_A, node_C, 2);
  graph.add_edge(node_A, node_D, 7);
  graph.add_edge(node_B, node_C, 6);
  graph.add_edge(node_B, node_D, 2);
  graph.add_edge(node_C, node_D, 2);

  Graph::Node *list[] = {node_A, node_B, node_C, node_D};
  const std::string names[] = {"A", "B", "C", "D"};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
    {
      Graph::Path path = find_shortest_path(list[i], list[j], &graph);
      std::cout << "shortest path length: ";
      std::cout << "(" << names[i] << "," << names[j] << ") ";
      std::cout << path.length << std::endl;
    }
}

void test_two()
{
  std::cout << "========================================" << std::endl;
  std::cout << "TEST_TWO (Marietta)" << std::endl;
  Map::Map *map = new Map::Map;
  Map::Intersection **nodes = make_marietta_nodes(map);
  make_marietta_edges(map, nodes);

  int s = 5637; // Atrium building
  int t = 212;  // Sweet Treats
  Graph::Path path = find_shortest_path(nodes[s], nodes[t], map);

  std::cout << "shortest path length: ";
  std::cout << path.length << " meters (";
  std::cout << path.length * 0.00062137 << " miles)";
  std::cout << std::endl;
  print_gps_coordinates(path);

  free(nodes);
  delete map;
}

int main()
{
  std::cout << "Hello" << std::endl;
  test_one();
  test_two();
}
