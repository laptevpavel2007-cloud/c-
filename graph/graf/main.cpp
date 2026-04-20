#include <iostream>
#include <cassert>
#include "class_graf.h"

int main() {
    Graph g;

    Node A("A"), B("B"), C("C"), D("D"), E("E");
    g.addNode(&A);
    g.addNode(&B);
    g.addNode(&C);
    g.addNode(&D);
    g.addNode(&E);

    auto addBidirectionalEdge = [&](Node* u, Node* v, int w) {
        g.addEdge(u, v);
        u->setWeight(v, w);
        v->setWeight(u, w);
        };

    addBidirectionalEdge(&A, &B, 2);
    addBidirectionalEdge(&A, &C, 1);
    addBidirectionalEdge(&B, &D, 3);
    addBidirectionalEdge(&C, &D, 1);
    addBidirectionalEdge(&D, &E, 2);

    BFS bfs(g);
    assert(bfs.connected(&A, &E) == true);
    assert(bfs.connected(&A, &B) == true);
    assert(bfs.connected(&B, &C) == true);
    assert(bfs.connected(&E, &A) == true);
    std::cout << "BFS: all connectivity tests passed.\n";

    DFS dfs(g);
    assert(dfs.connected(&A, &E) == true);
    assert(dfs.connected(&A, &B) == true);
    assert(dfs.connected(&B, &C) == true);
    assert(dfs.connected(&E, &A) == true);
    std::cout << "DFS: all connectivity tests passed.\n";

    
    g.removeEdge(&A, &C);

    assert(bfs.connected(&A, &C) == true);   
    assert(bfs.connected(&A, &E) == true);
    std::cout << "Edge removal: OK.\n";

    g.removeNode(&B);
    assert(bfs.connected(&A, &D) == false);
    assert(bfs.connected(&A, &C) == false); 
    assert(bfs.connected(&A, &E) == false);
    std::cout << "Node removal: OK.\n";

    return 0;
}