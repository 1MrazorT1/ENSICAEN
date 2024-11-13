#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "topo.h"
#include "time.h"

int main() {
    srand(time(NULL));
    // Create a graph
    int n = 15;
    double sigma = 0.3;
    Graph graph = createGraph(1,n,sigma);

    // Print the graph to the console
    //printConsoleGraph(graph);

    // Draw the graph to a file
    //drawGraph(graph, "graph.svg",0,1);

    //topological ordering
    /*
    topologicalSort(graph);
    printConsoleGraph(graph);
    drawGraph(graph, "topo.svg",1);
    */

    //topological ordering+earlyest dates
    /*
    computeEarliestStartDates(graph);
    printConsoleGraph(graph);
    drawGraph(graph, "dates.svg",2);
    */

    //topological ordering+earlyest dates+latest dates
    /*
    computeLatestStartDates(graph);
    printConsoleGraph(graph);
    drawGraph(graph, "dates.svg",3,1);
    */
    return 0;
}
