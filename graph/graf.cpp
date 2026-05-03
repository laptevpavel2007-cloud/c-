#include "class_graf.h"


Node::Node(const std::string& aname) : name(aname) {}

const std::string& Node::getName() const {
    return name;
}

void Node::addNeighbour(Node* neighbour, int weight) {
    if (neighbour) weights[neighbour] = weight;
}

void Node::removeNeighbour(Node* neighbour) {
    weights.erase(neighbour);
}

bool Node::isNeighbour(Node* node) const {
    return weights.find(node) != weights.end();
}

int Node::getWeight(Node* neighbour) const {
    auto it = weights.find(neighbour);
    if (it != weights.end()) return it->second;
    return INT_MAX;
}

Node::neighbour_iterator Node::nb_begin() const {
    return weights.begin();
}

Node::neighbour_iterator Node::nb_end() const {
    return weights.end();
}

void Graph::addNode(Node* node) {
    if (node) nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    if (!node) return;
    nodes.erase(node);
    for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addEdge(Node* begin, Node* end, int weight) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
        return;
    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (!begin || !end) return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

Graph::node_iterator Graph::begin() const {
    return nodes.begin();
}

Graph::node_iterator Graph::end() const {
    return nodes.end();
}

BFS::BFS(const Graph& agraph) : graph(agraph) {}

bool BFS::connected(Node* begin, Node* end) {
    if (!begin || !end) return false;
    std::queue<Node*> q;
    std::set<Node*> visited;
    q.push(begin);
    visited.insert(begin);

    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        if (curr == end) return true;
        for (Node::neighbour_iterator it = curr->nb_begin(); it != curr->nb_end(); ++it) {
            Node* nb = it->first;
            if (visited.find(nb) == visited.end()) {
                visited.insert(nb);
                q.push(nb);
            }
        }
    }
    return false;
}

DFS::DFS(const Graph& agraph) : graph(agraph) {}

bool DFS::dfs(Node* begin, Node* end) {
    if (begin == end) return true;
    visited.insert(begin);
    for (Node::neighbour_iterator it = begin->nb_begin(); it != begin->nb_end(); ++it) {
        Node* nb = it->first;
        if (visited.find(nb) == visited.end()) {
            if (dfs(nb, end)) return true;
        }
    }
    return false;
}

bool DFS::connected(Node* begin, Node* end) {
    visited.clear();
    return dfs(begin, end);
}

MarkedNode::MarkedNode(Node* anode, int amark, Node* aprev)
    : node(anode), mark(amark), prev(aprev) {
}

void PriorityQueue::push(Node* node, int mark, Node* prev) {
    MarkedNode mn(node, mark, prev);
    std::vector<MarkedNode>::iterator it = nodes.begin();
    while (it != nodes.end() && mark < it->mark) ++it;
    if (it == nodes.end()) nodes.push_back(mn);
    else nodes.insert(it, mn);
}

MarkedNode PriorityQueue::pop() {
    MarkedNode last = nodes.back();
    nodes.pop_back();
    return last;
}

bool PriorityQueue::empty() const {
    return nodes.empty();
}

Way::Way() : length(-1) {}

Way unroll(std::map<Node*, MarkedNode>& visited, Node* begin, Node* curr) {
    Way way;
    way.length = visited[curr].mark;
    while (curr != begin) {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
    }
    way.nodes.push_back(begin);
    std::reverse(way.nodes.begin(), way.nodes.end());
    return way;
}

Dijkstra::Dijkstra(const Graph& agraph) : graph(agraph) {}

Way Dijkstra::shortestWay(Node* begin, Node* end) {
    if (!begin || !end) return Way();

    PriorityQueue nodes;
    nodes.push(begin, 0, 0);
    std::map<Node*, MarkedNode> visited;

    while (!nodes.empty()) {
        MarkedNode cur = nodes.pop();
        visited[cur.node] = cur;

        if (cur.node == end) {
            return unroll(visited, begin, end);
        }

        for (Node::neighbour_iterator it = cur.node->nb_begin(); it != cur.node->nb_end(); ++it) {
            Node* nb = it->first;
            int weight = nb->getWeight(cur.node);
            if (weight == INT_MAX) continue;
            int newMark = cur.mark + weight;

            if (visited.find(nb) == visited.end()) {
                nodes.push(nb, newMark, cur.node);
            }
        }
    }
    return Way();
}