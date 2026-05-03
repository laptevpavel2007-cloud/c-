#include "class_graf.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    Graph g;

    struct Graph_str {
        int source;
        int target;
    };

    string name_file = "testgraph.txt";

    ifstream file(name_file);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл " << name_file << endl;
        return 1;
    }

    vector<Graph_str> graph_str;
    string line;

    getline(file, line);

    int max_id = 0;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        Graph_str rec;
        iss >> rec.source >> rec.target;
        graph_str.push_back(rec);
        if (rec.source > max_id) {
            max_id = rec.source;
        }
        if (rec.target > max_id) {
            max_id = rec.target;
        }
    }
    file.close();

    vector<Node*> id_to_node(max_id + 1, nullptr);

    for (const auto& rec : graph_str) {
        if (id_to_node[rec.source] == nullptr) {
            id_to_node[rec.source] = new Node(to_string(rec.source));
        }

        if (id_to_node[rec.target] == nullptr) {
            id_to_node[rec.target] = new Node(to_string(rec.target));
        }
    }

    for (Node* node : id_to_node) {
        if (node != nullptr) {
            g.addNode(node);
        }
    }

    for (const auto& rec : graph_str) {
        Node* src = id_to_node[rec.source];
        Node* dst = id_to_node[rec.target];
        g.addEdge(src, dst);
    }

    if (0 >= (int)id_to_node.size() || id_to_node[0] == nullptr || 4 >= (int)id_to_node.size() || id_to_node[4] == nullptr || 5 >= (int)id_to_node.size() || id_to_node[5] == nullptr) {
        cerr << "Ошибка: вершины 0, 4 или 5 не найдены в графе" << endl;
        for (Node* node : id_to_node) delete node;
        return 1;
    }

    Node* n0 = id_to_node[0];
    Node* n4 = id_to_node[4];
    Node* n5 = id_to_node[5];

    BFS bfs(g);
    DFS dfs(g);

    cout << "BFS: 0 -> 4 : " << (bfs.connected(n0, n4) ? "ДА" : "НЕТ") << endl;
    cout << "DFS: 0 -> 4 : " << (dfs.connected(n0, n4) ? "ДА" : "НЕТ") << endl;

    Dijkstra d(g);
    Way w = d.shortestWay(n0, n5);

    if (w.length >= 0) {
        cout << "Кратчайший путь от 0 до 5: длина = " << w.length << "\nПуть: ";
        for (size_t i = 0; i < w.nodes.size(); ++i)
            cout << w.nodes[i]->getName() << (i + 1 < w.nodes.size() ? " -> " : "");
        cout << endl;
    }
    else {
        cout << "Путь от 0 до 5 не найден" << endl;
    }

    for (Node* node : id_to_node) delete node;

    return 0;
}