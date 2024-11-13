#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "time.h"

int main() {
    srand(time(NULL));
    // Create a graph
    int n = 50;
    double sigma = 0.15;
    Graph graph = createGraph(0,n,sigma);

    // Print the graph to the console
    printConsoleGraph(graph);

    // Draw the graph to a file
    //drawGraph(graph, "graph.svg",0,0);

    // Perform a depth-first search
    //initialization of the array parents
    /*
    for(int i = 0; i < n; i++ )
        graph.parents[i]=-1;
    graphDFS(graph, 0);
    // Print the graph to the console
    printConsoleGraph(graph);
    // Draw the graph and the covering tree to files
    drawGraph(graph, "DFS-graph-tree.svg",2,0);
    drawGraph(graph, "DFS-tree.svg",1,0);
    */


    // Perform a breadth-first search
    /*
    graphBFS(graph, 0);
    printConsoleGraph(graph);
    // Draw the graph and the covering tree to files
    drawGraph(graph, "BFS-graph-tree.svg",2,0);
    drawGraph(graph, "BFS-tree.svg",1,0);
    */

    // compute the number of connected components.
    /*
    printf("Number of components : %d", numberOfComponents(graph));
    printConsoleGraph(graph);
    drawGraph(graph, "components-graph-tree.svg",2,0);
    drawGraph(graph, "components-tree.svg",1,0);
    */

    return 0;
}
