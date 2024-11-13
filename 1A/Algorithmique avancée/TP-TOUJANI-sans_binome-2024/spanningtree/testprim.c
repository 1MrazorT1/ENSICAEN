#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "prim.h"
#include "time.h"

int main() {
    srand(time(NULL));
    // Create a graph
    int n = 500;
    double sigma = 0.05;
    Graph graph = createGraph(0,n,sigma);
    // Print the graph to the console
    //printConsoleGraph(graph);

    // Draw the graph to a file
    //drawGraph (graph, "graph.svg",0,0);

    //initialization of the array parents
    /*
    for(int i = 0; i < n; i++ )
        graph.parents[i]=-1;
    */
    // Perform the minimal spanning tree from vertex 0
    //Prim(graph, 0);

    // Print the graph to the console
    //printConsoleGraph(graph);
    // Draw the graph and the spanning tree to files
    //drawGraph(graph, "prim-graph-tree.svg",2,0);
    //drawGraph(graph, "prim-tree.svg",1,0);


    return 0;
}
