#include "class_graf.h"

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    // Сначала удаляем ссылки на удаляемый узел из всех соседей
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }
    // Затем удаляем сам узел из множества
    nodes.erase(node);
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end()) return;
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

bool BFS::connected(Node* begin, Node* end) {
    std::queue<Node*> nodes;
    nodes.push(begin);
    std::set<Node*> visited;

    while (!nodes.empty()) {
        Node* next = nodes.front();
        nodes.pop();
        if (end == next) return true;
        visited.insert(next);
        for (auto it = next->nb_begin(); it != next->nb_end(); it++) {
            if (visited.find(*it) == visited.end())
                nodes.push(*it);
        }
    }
    return false;
}

bool DFS::connected(Node* begin, Node* end) {
    visited.clear();
    return connected(begin, end, 0);
}

bool DFS::connected(Node* begin, Node* end, int depth) {
    if (begin == end) return true;
    visited.insert(begin);
    for (auto it = begin->nb_begin(); it != begin->nb_end(); it++) {
        if (visited.find(*it) == visited.end()) {
            if (connected(*it, end, depth + 1)) return true;
        }
    }
    return false;
}

//MarkedNode PriorityQueue::pop() {
//    MarkedNode mn = nodes.back();
//    nodes.pop_back();
//    return mn;
//}
//
//void PriorityQueue::push(Node* node, int mark, Node* prev) {
//    MarkedNode mn(node, mark, prev);
//    auto it = nodes.begin();
//    while (it != nodes.end() && mark < it->mark) it++;
//    if (it == nodes.end()) nodes.push_back(mn);
//    else nodes.insert(it, mn);
//}
//
//Way unroll(std::map<Node*, MarkedNode> visited, Node* begin, Node* curr) {
//    Way way;
//    way.length = visited[curr].mark;
//    while (curr != begin) {
//        way.nodes.push_back(curr);
//        curr = visited[curr].prev;
//    }
//    way.nodes.push_back(begin);
//    return way;
//}