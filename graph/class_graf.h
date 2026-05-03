#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <climits>

class Node {
private:
    std::string name;
    std::map<Node*, int> weights;
public:
    Node(const std::string& aname);

    const std::string& getName() const;

    void addNeighbour(Node* neighbour, int weight = 1);
    void removeNeighbour(Node* neighbour);
    bool isNeighbour(Node* node) const;
    int getWeight(Node* neighbour) const;

    typedef std::map<Node*, int>::const_iterator neighbour_iterator;
    neighbour_iterator nb_begin() const;
    neighbour_iterator nb_end() const;
};

class Graph {
private:
    std::set<Node*> nodes;
public:
    typedef std::set<Node*>::const_iterator node_iterator;

    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end, int weight = 1);
    void removeEdge(Node* begin, Node* end);

    node_iterator begin() const;
    node_iterator end() const;
};

class BFS {
private:
    const Graph& graph;
public:
    BFS(const Graph& agraph);
    bool connected(Node* begin, Node* end);
};

class DFS {
private:
    const Graph& graph;
    std::set<Node*> visited;
    bool dfs(Node* begin, Node* end);
public:
    DFS(const Graph& agraph);
    bool connected(Node* begin, Node* end);
};

struct MarkedNode {
    Node* node;
    int   mark;
    Node* prev;
    MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0);
};

class PriorityQueue {
private:
    std::vector<MarkedNode> nodes;
public:
    void push(Node* node, int mark, Node* prev);
    MarkedNode pop();
    bool empty() const;
};

struct Way {
    std::vector<Node*> nodes;
    int length;
    Way();
};

Way unroll(std::map<Node*, MarkedNode>& visited, Node* begin, Node* curr);

class Dijkstra {
private:
    const Graph& graph;
public:
    Dijkstra(const Graph& agraph);
    Way shortestWay(Node* begin, Node* end);
};

#endif