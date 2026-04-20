#ifndef CLASS_GRAF_H
#define CLASS_GRAF_H

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

class Node;

class Graph {
    std::set<Node*> nodes;
public:
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);

    auto begin() const { return nodes.begin(); }
    auto end() const { return nodes.end(); }
};

class Node {
    std::string name;
    std::set<Node*> neighbours;
    std::map<Node*, int> weights;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);

public:
    Node(const std::string& aname) : name(aname) {}

    const std::string& getName() const { return name; }

    void setWeight(Node* neighbour, int weight) {
        weights[neighbour] = weight;
    }

    int getWeight(Node* neighbour) const {
        auto it = weights.find(neighbour);
        return it != weights.end() ? it->second : 1;
    }

    auto nb_begin() const { return neighbours.begin(); }
    auto nb_end() const { return neighbours.end(); }

    friend class Graph;
};

typedef std::set<Node*>::const_iterator node_iterator;

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth);
public:
    DFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

struct MarkedNode {
    Node* node;
    int mark;
    Node* prev;
    MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0)
        : node(anode), mark(amark), prev(aprev) {
    }
};

class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};

struct Way {
    std::vector<Node*> nodes;
    int length;
    Way() : length(-1) {}
};

//class Dijkstra {
//    const Graph& graph;
//public:
//    Dijkstra(const Graph& agraph) : graph(agraph) {}
//    Way shortestWay(Node* begin, Node* end);
//};

#endif