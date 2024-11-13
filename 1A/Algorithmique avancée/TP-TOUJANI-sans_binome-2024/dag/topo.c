/**
 * @file topo.c
 *
 * @brief This file implements based on the topological ordering.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../stack/stack.h"


/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    int k = graph.numberVertices - 1;
    for(int i = 0; i < graph.numberVertices; i++){
        if(strcmp(graph.array[i]->key, "vert") != 0){
            graphDFS(graph, i);
            List L = graph.array[i]->key;
            while(strcmp(graph.array[i]->key, "vert") == 0){
                graph.topological_ordering[k] = i;
                k = k - 1;
            }
        }
    }
}


/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    for(int i = 0; i < graph.numberVertices; i++){
        int* predecesseurs = malloc(sizeof(int)*(graph.numberVertices));
        for(int j = 0; j < graph.numberVertices; j++){
            if(graph.array[j]->nextCell->value == i){
                predecesseurs[j] = j;
            }else{
                predecesseurs[j] = -1;
            }
        }
        double dtot = 0;
        for(int j = 0; j < graph.numberVertices; j++){
            double x1 = graph.xCoordinates[i];
            double y1 = graph.yCoordinates[i];
            double x2 = graph.xCoordinates[j];
            double y2 = graph.yCoordinates[j];
            if(predecesseurs[j] != -1){
                Graph g = createGraph(1, graph.numberVertices - j, graph.sigma);
                computeEarliestStartDates(g);
                if(dtot < g.earliest_start[graph.numberVertices - j] + distance(x1,y1,x2,y2)){
                    dtot = g.earliest_start[graph.numberVertices - j] + distance(x1,y1,x2,y2);
                }
            }else{
                if(dtot < 0 + distance(x1,y1,x2,y2)){
                    dtot = 0 + distance(x1,y1,x2,y2);
                }
            }
        }
        graph.earliest_start[i] = dtot;
    }
    return;
}


/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph){
    double max_earliest_start_date = 0;
    for(int i = 0; i < graph.numberVertices; i++){
        if(max_earliest_start_date < graph.earliest_start[i]){
            max_earliest_start_date = graph.earliest_start[i];
        }
    }
    for(int i = 0; i < graph.numberVertices; i++){
        int* successeurs = malloc(sizeof(int)*(graph.numberVertices));
        List L = graph.array[i];
        for(int j = 0; j < graph.numberVertices; j++){
            if(L != NULL){
                successeurs[j] = L->value;
                L = L->nextCell;
            }else{
                successeurs[j] = -1;
            }
        }
        double dtard = 0;
        for(int j = 0; j < graph.numberVertices; j++){
            if(successeurs[j] != -1){
                Graph g = createGraph(1, graph.numberVertices - j, graph->sigma);
                computeLatestStartDates(g);
                double x1 = graph.xCoordinates[i];
                double y1 = graph.yCoordinates[i];
                double x2 = graph.xCoordinates[successeurs[j]];
                double y2 = graph.yCoordinates[successeurs[j]];
                if(dtard > g.latest_start[graph.numberVertices - j] - distance(x1,y1,x2,y2)){
                    dtard = g.latest_start[graph.numberVertices - j] - distance(x1,y1,x2,y2);
                }
            }else{
                if(dtard > max_earliest_start_date){
                    dtard = max_earliest_start_date;
                }
            }
        }
        graph.latest_start[i] = dtard;
    }
    return;
}