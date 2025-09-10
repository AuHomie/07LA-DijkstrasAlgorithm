#include <iostream>
#include <list>
#include <string>

struct Pair {

int node;
int weight;
};

class graph{

    Graph(string);
    int shortesdtCost(int start, int finish);
private:
    list<Pair>* adjList;
};


