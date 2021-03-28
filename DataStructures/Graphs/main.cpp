#include <iostream>
#include "UndirectedGraph.h"

using namespace std;

int main() {

    auto g = UndirectedGraph<int, int>();
    g.add_node(3, 5);
    g.add_node(1, 5);
    g.add_node(2, 5);

    g.add_edge(1, 2);
    g.add_edge(1, 3);

    return 0;
}
