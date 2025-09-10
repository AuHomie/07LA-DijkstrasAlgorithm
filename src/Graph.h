#include <iostream>
#include <list>
#include <string>

struct Pair {

    Pair(int n, int w){
    node = n;
    weight = w;
    }

    int weight;
    int node;
};

class Graph{

    public:
    Graph(std::string);
    int shortesdtCost(int start, int finish);


private:
    std::list<Pair>* adjList;
    int numNodes;
};


